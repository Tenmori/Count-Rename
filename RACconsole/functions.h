#pragma once
class functions
{
public:
	std::vector<std::filesystem::path> read_directory(std::string path);
	void rename_directory_files(pathvec fileList, std::string newName, std::string path);
	std::string choose_directory();
	std::string enter_name();
};

