#include "core.h"
#include <sstream>
#include <ctime>
#include <fstream>
#include <QDebug>
#include <iostream>

/*
 * Where the magic happens /s
 *
 * Collection of the two key functions and two outdated ones.
 *
 *
 *
 */

core::core()
{

}

namespace fs = std::experimental::filesystem;

/*
    Takes user input to determine the name format for what the files shall be renamed to.
    No longer relevant. Only used in console version.
*/
std::string core::enter_name()
{
    std::string name;
    std::cout << "Enter new name format: ";
    std::getline(std::cin, name);

    return name;
}


/*
    User enters folder path. Files in folder will be renamed to enter_name()'s input.
    No longer relevant. Only used in console version.
*/
std::string core::choose_directory()
{
    std::string path;
    std::cout << "Enter Path: ";
    std::getline(std::cin, path);

    if (fs::exists(fs::path(path)))
    {
        return path;
    }
    else
    {
        throw std::invalid_argument("Path does not exist / is not valid.");
    }
}

/*
    Copies all files and renames them into a separate copy folder.
*/
pathvec core::rename_directory_files(int actionType, pathvec fileList, std::string newName, std::string path, int countStart)
{
    //Used only in console version
    //The digit from which we start the renaming process at.
    //EG: newName X; Backgrounds 26
    //std::string startCountInput;

    //Location of files being renamed.
    fs::path p(path);

    pathvec newFileList;

    //Check if name is null
    if (static_cast<int>(newName.size()) > 0)
    {
        newName = newName + " ";
    }

    //Maximum number of possible padded zeroes required for padding.
    int upper_count;

    if (countStart == 0)
    {
        upper_count = static_cast<int>(fileList.size());
    }else
    {
        upper_count = countStart + static_cast<int>(fileList.size());

    }

    //Used only in console version
    //std::cout << "Enter the number from which your file count begins: ";
    //std::getline(std::cin, startCountInput);

    switch(actionType)
    {
        //Creates a copy of all files in list
        case 0:
            //Location of where copies will be placed.
            fs::create_directories(p / "Output");

            for (size_t i = 0; i < fileList.size(); i++)
            {
                //Current number being appended to renamed files.
                int cur_count = (countStart + static_cast<int>(i));

                std::string extension = fs::path(fileList.at(i)).extension().u8string();
                std::string cur_number = std::to_string(cur_count);
                std::string padding = zeroPad(upper_count, cur_count);

                newFileList.push_back(p / "Output" / (newName + padding + cur_number + extension));

                fs::copy(fileList.at(i), p / "Output" / (newName + padding + cur_number + extension));
            }
        break;

        //Replaces all files in list
        case 1:
            for (size_t i = 0; i < fileList.size(); i++)
            {
                //Current number being appended to renamed files.
                int cur_count = (countStart + static_cast<int>(i));

                std::string extension = fs::path(fileList.at(i)).extension().u8string();
                std::string cur_number = std::to_string(cur_count);
                std::string padding = zeroPad(upper_count, cur_count);

                newFileList.push_back(p / (newName + padding + cur_number + extension));

                fs::rename(fileList.at(i), p / (newName + padding + cur_number + extension));
            }
        break;
    }

    return newFileList;
}

/*
    Reads all files in a fold, takes a list and returns.
*/
pathvec core::read_directory(std::string path)
{
    fs::path p(path);
    pathvec fileList;

    if (fs::exists(p))
    {
        for (const auto& entry : fs::directory_iterator(p))
        {
            //std::cout << entry.path() << "\n" << std::endl;
            fileList.push_back(entry.path());
        }

        return fileList;
    }
    else
    {
        throw std::invalid_argument("Path does not exist / is not valid.");
    }
}

/*
    Determines the amount of padded zeroes necessary.
*/
std::string core::zeroPad(int upper_count, int cur_count)
{
    int upper_zero_count = 0;
    int cur_zero_count = 0;
    size_t zero_pad_amount;

    while (upper_count /= 10)
        upper_zero_count++;

    while (cur_count /= 10)
        cur_zero_count++;

    zero_pad_amount = static_cast<size_t>(upper_zero_count - cur_zero_count);

    std::string zeroPad(zero_pad_amount, '0');
    return zeroPad;
}

/*
    Records all changes made to files by this program.
*/
void core::document_changes(pathvec from, pathvec to)
{
    fs::path p("changelog");
    std::ofstream myfile;

    if (!fs::exists(p))
    {
        fs::create_directory(p);
    }

    const int MAXLEN = 20;
    char s[MAXLEN];
    time_t t = time(nullptr);
    strftime(s, MAXLEN, "%Y-%m-%d.txt", localtime(&t));
    //std::cout << s << '\n';

    myfile.open(p/s, std::ios_base::app);

    for (size_t i = 0; i < from.size(); i++)
    {
        myfile << from.at(i) << "->" << to.at(i) << std::endl;
    }

    myfile.close();
}

/*
    Isolates all the names in a file list.
    Typically removes the paths and extensions.
*/

std::vector<std::string> core::isolateName(pathvec fileList)
{
   std::vector<std::string> nameList;

   //for (size_t i = 0; i < fileList.size(); i++)
           //std::cout << fileList.at(i) << std::endl;

   //std::cout << "LIST 1_________________" << std::endl;
    for (size_t i = 0; i < fileList.size(); i++)
    {
        std::string curName = fileList.at(i).u8string();

        if (curName.rfind("\\") != std::string::npos)
            curName.erase(0, curName.rfind("\\")+1);

        if (curName.rfind(".") != std::string::npos && (curName.size() - curName.rfind(".")) < 5 &&
                curName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_", curName.rfind(".")+1) == std::string::npos)
            curName.erase(curName.rfind("."));

        nameList.push_back(curName);

    }
    //std::cout << "LIST 2_________________" << std::endl;
    //for (size_t i = 0; i < nameList.size(); i++)
            //std::cout << nameList.at(i) << std::endl;

    return nameList;
}

/*
    Isolates the extension to later add back.
    Works in tandem with the function above.
 */
std::vector<std::string> core::isolateExtension (pathvec fileList)
{
    std::vector<std::string> extensionList;

    for (size_t i = 0; i < fileList.size(); i++)
    {
        std::string extension = fileList.at(i).u8string();

        extension.erase(0, extension.rfind(".") + 1);

        if (extension.length() < 1)
            extension = "NULL";

        if (extension.length() > 3)
            extension = "NULL";

        if (extension.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos)
            extension = "NULL";

        extensionList.push_back(extension);
    }

    return extensionList;
}

/*
    Removes a set phrase from all the files in a filelist
*/
std::vector<std::string> core::removePhrase(std::vector<std::string> nameList, std::string phraseToRemove)
{
    std::vector<std::string> cleanedNameList;

    for (size_t i = 0; i < nameList.size(); i++)
    {
        std::string name = nameList.at(i);

        if (name.size() > phraseToRemove.size())
        {
            std::string::size_type i = name.find(phraseToRemove);

            if( i != std::string::npos)
            {
                name.erase(i, phraseToRemove.length());
                cleanedNameList.push_back(name);
                //std::cout << name << "\n";
            }
            else
            {
                cleanedNameList.push_back(name);
            }
        }
        else
        {
            cleanedNameList.push_back(name);
        }
    }

    return cleanedNameList;
}

/*
 Types:
 1 - Period "."
 2 - Underscore "_"
 3 - Hyphen "-"
 4 - Left Brace "{"
 5 - Right Brace "}"
 6 - Left Bracket "["
 7 - Right Bracket "]"
 8 - Left Parentheses "("
 9 - Right Parentheses ")"
 10 - Space " "
 */
std::vector<std::string> core::removeSpecials(std::vector<std::string> nameList, int removeSpecial, int singleReplaceType)
{
    std::vector<std::string> newNameList;
    std::string specials[] = {".", "_", "-", "{", "}", "[", "]", "(", ")", " "};

    for (size_t i = 0; i < nameList.size(); i++)
    {
        if (nameList.at(i).find(".") != std::string::npos)
        {
            std::string curName = nameList.at(i);

            size_t specialPos = curName.find(specials[removeSpecial]);

            while(specialPos != std::string::npos)
            {
                curName.replace(specialPos, 1, specials[singleReplaceType]);
                specialPos = curName.find(specials[removeSpecial], specialPos+1);
            }

            //std::cout << curName << std::endl;

            newNameList.push_back(curName);

        }else
        {
            newNameList.push_back(nameList.at(i));
        }
    }
    return newNameList;
}

/*
    Removes all of the selected of the following when they appear in pairs
    -Parentheses                (pair 1)
    -Brackets                   (pair 2)
    -Braces                     (pair 3)
    -Greater / Less than signs  (pair 4)

    Note to self: Must balance for situations where pairs are lopesided, as in
    there are more "[" than "]".
*/
std::vector<std::string> core::removePairs(std::vector<std::string> nameList, std::string pair)
{
    char pair1 = pair.at(0);
    char pair2 = pair.at(1);
    std::vector<std::string> newNameList;

    for (size_t i = 0; i < nameList.size(); i++)
    {
        if (nameList.at(i).find(pair1) != std::string::npos && nameList.at(i).find(pair2) != std::string::npos)
        {
            std::vector<size_t> positionsA;
            std::vector<size_t> positionsB;
            std::string curName = nameList.at(i);

            size_t posA = nameList.at(i).find(pair1);
            size_t posB = nameList.at(i).find(pair2);

            while (posA != std::string::npos && posB != std::string::npos)
            {

                positionsA.push_back(posA);
                //std::cout << posA << std::endl;
                posA = curName.find(pair1, posA+1);

                positionsB.push_back(posB);
                //std::cout << posB << std::endl;
                posB = curName.find(pair2, posB+1);

            }

            if (positionsA.size() == positionsB.size())
            {
                for (size_t j = positionsA.size(); j > 0; j--)
                {
                    //std::cout << curName << std::endl;

                    std::string cleanedName = curName.erase(positionsA.at(j - 1), (positionsB.at(j - 1) - positionsA.at(j-1) + 1));

                    //std::cout << cleanedName << std::endl;
                    if (j== 1)
                        newNameList.push_back(cleanedName);
                }
            }
            //std::cout << "\n" << "________" << std::endl;
        }else
        {
            newNameList.push_back(nameList.at(i));
        }


    }

    //std::cout << newNameList.size() << std::endl;

    return newNameList;
}

std::vector<std::string> core::trimWhiteSpace(std::vector<std::string> nameList)
{
    const std::string fill = " ";
    const std::string whitespace = " \t";

    std::vector<std::string> newNameList;
    std::string curName;

    for (size_t i = 0; i < nameList.size(); i++)
    {
        curName = nameList.at(i);
        size_t first = curName.find_first_not_of(' ');
        size_t last = curName.find_last_not_of(' ');
        curName = curName.substr(first, (last-first+1));

        auto beginSpace = curName.find_first_of(whitespace);
        while (beginSpace != std::string::npos)
        {
            const auto endSpace = curName.find_first_not_of(whitespace, beginSpace);
            const auto range = endSpace - beginSpace;

            curName.replace(beginSpace, range, fill);

            const auto newStart = beginSpace + fill.length();
            beginSpace = curName.find_first_of(whitespace, newStart);
        }
        newNameList.push_back(curName);
    }

    return newNameList;
}

/*
 * need to add . and _ and -
 */
pathvec core::cleanUp(pathvec fileList, std::string path, bool phrase, std::string phraseToRemove)
{
    std::vector<std::string> nameList = isolateName(fileList);
    std::vector<std::string> extensionList = isolateExtension(fileList);
    fs::path p(path);
    pathvec newFileList;


    if (phrase)
    {
        nameList = removePhrase(nameList, phraseToRemove);
    }
    //for (size_t i = 0; i < nameList.size(); i++)
        //std::cout << nameList.at(i) << std::endl;

    //std::cout << "_________" << "\n"<< std::endl;

    nameList = removePairs(nameList, "[]");
    //for (size_t i = 0; i < nameList.size(); i++)
        //std::cout << nameList.at(i) << std::endl;
    nameList = removePairs(nameList, "()");
    //for (size_t i = 0; i < nameList.size(); i++)
        //std::cout << nameList.at(i) << std::endl;
    nameList = removePairs(nameList, "{}");

    nameList = trimWhiteSpace(nameList);

    nameList = removeSpecials(nameList, 0, 9);

    /*for (size_t i = 0; i < nameList.size(); i++)
        std::cout << nameList.at(i) << std::endl;

    std::cout << "__________________________\n" << std::endl;

    for (size_t i = 0; i < nameList.size(); i++)
        std::cout << extensionList.at(i) << std::endl;*/

    for (size_t i = 0; i < fileList.size(); i++)
        std::cout << fileList.at(i) << std::endl;

    if (nameList.size() == extensionList.size())
    {
        for (size_t i = 0; i < nameList.size(); i++)
        {

            //+ extensionList.at(i)
            //fs::rename(fileList.at(i), p / (nameList.at(i)));

            if (extensionList.at(i).compare("NULL") == 0)
            {
                fs::rename(fileList.at(i), p / nameList.at(i));
                std::cout << nameList.at(i) << std::endl;
                newFileList.push_back(p / nameList.at(i));
            }else
            {
                fs::rename(fileList.at(i), p / (nameList.at(i) + "." + extensionList.at(i)));
                std::cout << nameList.at(i) << "." << extensionList.at(i) << std::endl;
                newFileList.push_back(p / (nameList.at(i) + "." + extensionList.at(i)));
            }
        }
    }

    return newFileList;
}

/*
 Takes the most recent rename and undoes it.
 */
void core::undo(pathvec originalList, pathvec currentList)
{
    if (originalList.size() == currentList.size())
    {
        for (size_t i = 0; i < originalList.size(); i++)
        {
            std::cout << "Here 3" << std::endl;
            fs::rename(currentList.at(i), originalList.at(i));
            std::cout << "Here 3.1" << std::endl;
        }
        std::cout << "Here 4" << std::endl;
    }
    std::cout << "Here 5" << std::endl;
}
