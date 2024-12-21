#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <Windows.h>
#include <utility>
#include <cstdint>
#include <algorithm>
#include "command.h"
#include "env_vars.h"


struct FileInfo_s {
	bool isFile;
	std::string attributes;
	//std::string owner;
	uint64_t size;
	SYSTEMTIME time;
	std::string name;
};


class LsCommand : public Command {
public:
	LsCommand(const std::string& flags, const std::vector<std::string>& arguments);

	void execute() override;

	void errorChecking() override;

	void validatePaths();

	std::vector<WIN32_FIND_DATAA> getFilesFindData(const std::string& path);

	void handleFlags(std::vector<std::vector<WIN32_FIND_DATAA>>& dirsFilesFindData);

	void handleFlagsForDir(std::vector<WIN32_FIND_DATAA>& filesFindData);
	
	void removeHiddenFiles(std::vector<WIN32_FIND_DATAA>& filesFindData);

	void sortByTime(std::vector<WIN32_FIND_DATAA>& filesFindData);

	void sortByAlphaBet(std::vector<WIN32_FIND_DATAA>& filesFindData);

	void reverseOrder(std::vector<WIN32_FIND_DATAA>& filesFindData);

	void printFilesNames(const std::vector<WIN32_FIND_DATAA>& filesFindData);

	void printLongListing(const std::vector<WIN32_FIND_DATAA>& filesFindData);

	FileInfo_s getFileInfo(const WIN32_FIND_DATAA& filesFindData);

	void assignAttributes(FileInfo_s& fileInfo, const DWORD& fileAttributes);

	void assignSize(FileInfo_s& fileInfo, const DWORD& fileSizeHigh, const DWORD& fileSizeLow);

	void assignTime(FileInfo_s& fileInfo, const FILETIME& time);

};