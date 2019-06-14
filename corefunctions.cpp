#include "corefunctions.h"
#include <sstream>

/*
 * Where the magic happens /s
 *
 * Collection of the two key functions and two outdated ones.
 *
 *
 *
 */

coreFunctions::coreFunctions()
{

}

namespace fs = std::experimental::filesystem;

/*
    Takes user input to determine the name format for what the files shall be renamed to.
    No longer relevant. Only used in console version.
*/
std::string coreFunctions::enter_name()
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
std::string coreFunctions::choose_directory()
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
void coreFunctions::rename_directory_files(pathvec fileList, std::string newName, std::string path, int countStart)
{
    //Used only in console version
    //The digit from which we start the renaming process at.
    //EG: newName X; Backgrounds 26
    //std::string startCountInput;

    //Location of files being renamed.
    fs::path p(path);

    //Location of wheree copies will be placed.
    fs::create_directories(p / "Output");

    //Maximum number of possible padded zeroes required for padding.
    int upper_count = countStart + static_cast<int>(fileList.size());


    //Used only in console version
    //std::cout << "Enter the number from which your file count begins: ";
    //std::getline(std::cin, startCountInput);

    for (size_t i = 0; i < fileList.size(); i++)
    {
        //Current number being appended to renamed files.
        int cur_count = (countStart + static_cast<int>(i));

        std::string extension = fs::path(fileList.at(i)).extension().u8string();
        std::string cur_number = std::to_string(cur_count);
        std::string padding = zeroPad(upper_count, cur_count);

        fs::copy(fileList.at(i), p / "Output" / (newName + " " + padding +cur_number + extension));

        //Function offers option to rename source files instead of creating a copy.
        //rename(fileList.at(i), p / "Output" / (newName + " " + cur_number + extension));
    }
}

/*
    Reads all files in a fold, takes a list and returns.
*/
std::vector<std::experimental::filesystem::path> coreFunctions::read_directory(std::string path)
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
std::string coreFunctions::zeroPad(int upper_count, int cur_count)
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
