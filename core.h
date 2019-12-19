#ifndef CORE_H
#define CORE_H
#include "stdheader.h"

class core
{
public:
    core();
    pathvec read_directory(std::string path);
    std::string choose_directory();
    std::string enter_name();
    std::string zeroPad(int upper_count, int cur_count);

    pathvec rename_directory_files(int actionType, pathvec fileList, std::string newName, std::string path, int countStart);
    void document_changes(pathvec from, pathvec to);
    pathvec cleanUp(pathvec fileList, std::string path, bool phrase, std::string phraseToRemove);
    void undo(pathvec originalList, pathvec currentList);

    std::vector<std::string> isolateName(pathvec fileList);
    std::vector<std::string> isolateExtension (pathvec fileList);
    std::vector<std::string> trimWhiteSpace(std::vector<std::string> nameList);
    std::vector<std::string> removePhrase(std::vector<std::string> nameList, std::string phraseToRemove);
    std::vector<std::string> removePairs(std::vector<std::string> nameList, std::string pair);
    std::vector<std::string> removeSpecials(std::vector<std::string> nameList, int removeSpecial, int singleReplaceType);
};

#endif // COREFUNCTIONS_H
