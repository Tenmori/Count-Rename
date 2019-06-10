#include "stdafx.h"
#include "functions.h"

namespace fs = std::filesystem;

std::string functions::enter_name()
{
	std::string name;
	std::cout << "Enter new name format: ";
	std::getline(std::cin, name);

	return name;
}

std::string functions::choose_directory()
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

void functions::rename_directory_files(pathvec fileList, std::string newName, std::string path)
{
	std::string startCountInput;
	int startCount;
	fs::path p(path);
	fs::create_directories(p / "Output");

	std::cout << "Enter the number from which your file count begins: ";
	std::getline(std::cin, startCountInput);

	startCount = std::stoi(startCountInput);

	for (int i = 0; i < fileList.size(); i++)
	{
		std::string extension = fs::path(fileList.at(i)).extension().u8string();
		std::string cur_number = "00" + std::to_string(startCount + i);
		
		fs::copy(fileList.at(i), p / "Output" / (newName + " " + cur_number + extension));

		//rename(fileList.at(i), p/"Output"/(newName + " " + std::to_string(i) + extension));
	}
}

std::vector<std::filesystem::path> functions::read_directory(std::string path)
{
	fs::path p(path);
	pathvec fileList;

	for (const auto& entry : fs::directory_iterator(p))
	{
		//std::cout << entry.path() << "\n" << std::endl;
		fileList.push_back(entry.path());
	}

	return fileList;
}
