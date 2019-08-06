#ifndef COREFUNCTIONS_H
#define COREFUNCTIONS_H
#include "stdheader.h"

class coreFunctions
{
public:
    coreFunctions();
    std::vector<std::experimental::filesystem::path> read_directory(std::string path);
    void rename_directory_files(int actionType, pathvec fileList, std::string newName, std::string path, int countStart);
    std::string choose_directory();
    std::string enter_name();
    std::string zeroPad(int upper_count, int cur_count);
    void document_changes(pathvec from, pathvec to);
};

#endif // COREFUNCTIONS_H
