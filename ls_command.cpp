#include "ls_command.h"

LsCommand::LsCommand(const std::string& flags, const std::vector<std::string>& arguments) :
	Command(flags, arguments, LS_VALID_FLAGS) {}

void LsCommand::execute() {
	try {
		errorChecking();
	}
	catch (const std::runtime_error& exception) {
		error.doesExist = true;
		error.message = exception.what();
		return;
	}
	if (arguments.empty()) {
		arguments.push_back(EnvVars::getVar("PWD"));
	}
	validatePaths();
	if (arguments.empty()) {
		return;
	}
	std::vector<std::vector<WIN32_FIND_DATAA>> dirsFilesFindData{};
	for (const std::string& path : arguments) {
		dirsFilesFindData.push_back(getFilesFindData(path));
	}
	handleFlags(dirsFilesFindData);
	
	output.doesExist = true;
	for (const std::vector<WIN32_FIND_DATAA>& dir : dirsFilesFindData) {
		for (const WIN32_FIND_DATAA& findData : dir) {
			output.message += findData.cFileName;
			output.message += "    ";
			
		}
		output.message += "\n\n";
	}
	
}

void LsCommand::errorChecking() {
	if (!areFlagsValid()) {
		throw std::runtime_error("cd: invalid option -- '" + flags + "'");
	}
}

void LsCommand::validatePaths() {
	for (auto i = arguments.begin(); i != arguments.end();) {
		std::filesystem::path path(*i);
		if (!std::filesystem::exists(path)){
			if (!std::filesystem::exists(std::filesystem::path(EnvVars::getVar("PWD") / path))) {
				error.doesExist = true;
				error.message += "ls: cannot access '" + *i + "': No such file or directory\n";
				i = arguments.erase(i);
			}
			else {
				*i = EnvVars::getVar("PWD") + "\\" + *i;
				++i;
			}
		}
		else {
			++i;
		}
	}
}

std::vector<WIN32_FIND_DATAA> LsCommand::getFilesFindData(const std::string& path) {
	std::vector<WIN32_FIND_DATAA> filesFindData{};
	WIN32_FIND_DATAA findData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	std::string searchPath = std::filesystem::is_directory(path) ? path + "\\*" : path;
	hFind = FindFirstFileA(searchPath.c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE) {
		writeErrorMessage("ls: Unable to open directory " + path);
		return filesFindData;
	}
	do {
		filesFindData.push_back(findData);
	} while (FindNextFileA(hFind, &findData) != 0);
	FindClose(hFind);
	return filesFindData;
}

void LsCommand::handleFlags(const std::vector<std::vector<WIN32_FIND_DATAA>>& dirsFilesFindData) {
	
}

FileInfo_s LsCommand::getFileInfo(const WIN32_FIND_DATAA& fileFindData) {
	FileInfo_s fileInfo{};
	fileInfo.isFile = !(fileFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	assignAttributes(fileInfo, fileFindData.dwFileAttributes);
	assignSize(fileInfo, fileFindData.nFileSizeHigh, fileFindData.nFileSizeLow);
	assignTime(fileInfo, fileFindData.ftLastWriteTime);
	fileInfo.name = fileFindData.cFileName;
	return fileInfo;
}

void LsCommand::assignAttributes(FileInfo_s& fileInfo, const DWORD& attributes) {
	fileInfo.attributes += (attributes & FILE_ATTRIBUTE_READONLY) ? "R" : "-";
	fileInfo.attributes += (attributes & FILE_ATTRIBUTE_HIDDEN) ? "H" : "-";
	fileInfo.attributes += (attributes & FILE_ATTRIBUTE_SYSTEM) ? "S" : "-";
	fileInfo.attributes += (attributes & FILE_ATTRIBUTE_ARCHIVE) ? "A" : "-";
	fileInfo.attributes += (attributes & FILE_ATTRIBUTE_REPARSE_POINT) ? "L" : "-";
}

void LsCommand::assignSize(FileInfo_s& fileInfo, const DWORD& fileSizeHigh, const DWORD& fileSizeLow) {
	fileInfo.size = (static_cast<uint64_t>(fileSizeHigh) << 32) | fileSizeLow;
}

void LsCommand::assignTime(FileInfo_s& fileInfo, const FILETIME& fileTime) {
	SYSTEMTIME sysTime;
	FileTimeToSystemTime(&fileTime, &sysTime);
	fileInfo.time = sysTime;
}
