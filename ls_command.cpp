#include "ls_command.h"

static bool cmpByTime(const WIN32_FIND_DATAA& first, const WIN32_FIND_DATAA& second);

static bool cmpByAlphaBet(const WIN32_FIND_DATAA& first, const WIN32_FIND_DATAA& second);

static std::string getLongListingFormatString(const FileInfo_s& file, bool humanReadable);

static std::string convertToHumanReadable(uint64_t size);

static std::string getSystemTimeString(const SYSTEMTIME& time);

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

void LsCommand::handleFlags(std::vector<std::vector<WIN32_FIND_DATAA>>& dirsFilesFindData) {
	for (std::vector<WIN32_FIND_DATAA>& dir : dirsFilesFindData) {
		handleFlagsForDir(dir);
	}
}

void LsCommand::handleFlagsForDir(std::vector<WIN32_FIND_DATAA>& filesFindData) {
	/*
	l- long listed
	a- all
	h- human readable
	R- recursive
	t- time sorted
	r- reverse
	*/
	if (std::find(flags.begin(), flags.end(), 'a') == flags.end()) {
		removeHiddenFiles(filesFindData);
	}
	if (std::find(flags.begin(), flags.end(), 't') != flags.end()) {
		sortByTime(filesFindData);
	}
	else {
		sortByAlphaBet(filesFindData);
	}
	if (std::find(flags.begin(), flags.end(), 'r') != flags.end()) {
		reverseOrder(filesFindData);
	}
	if (std::find(flags.begin(), flags.end(), 'l') == flags.end()) {
		printFilesNames(filesFindData);
	}
	else {
		printLongListing(filesFindData);
	}
}

void LsCommand::removeHiddenFiles(std::vector<WIN32_FIND_DATAA>& filesFindData) {
	for (auto i = filesFindData.begin(); i != filesFindData.end();) {
		if (i->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN ||
			std::string(i->cFileName).at(FIRST_INDEX) == '.') {
			i = filesFindData.erase(i);
		}
		else {
			++i;
		}
	}
}

void LsCommand::sortByTime(std::vector<WIN32_FIND_DATAA>& filesFindData) {
	std::sort(filesFindData.begin(), filesFindData.end(), cmpByTime);
}

void LsCommand::sortByAlphaBet(std::vector<WIN32_FIND_DATAA>& filesFindData) {
	std::sort(filesFindData.begin(), filesFindData.end(), cmpByAlphaBet);
}

void LsCommand::reverseOrder(std::vector<WIN32_FIND_DATAA>& filesFindData) {
	std::reverse(filesFindData.begin(), filesFindData.end());
}

void LsCommand::printFilesNames(const std::vector<WIN32_FIND_DATAA>& filesFindData) {
	output.doesExist = true;
	for (const WIN32_FIND_DATAA& file : filesFindData) {
		output.message += file.cFileName;
		output.message += "    ";
	}
}

void LsCommand::printLongListing(const std::vector<WIN32_FIND_DATAA>& filesFindData) {
	std::vector<FileInfo_s> files{};
	bool humanReadable = std::find(flags.begin(), flags.end(), 'h') != flags.end();
	output.doesExist = true;
	for (const WIN32_FIND_DATAA& findData : filesFindData) {
		files.push_back(getFileInfo(findData));
	}
	for (const FileInfo_s& file : files) {
		output.message += getLongListingFormatString(file, humanReadable);
	}
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

static bool cmpByTime(const WIN32_FIND_DATAA& first, const WIN32_FIND_DATAA& second) {
	int result = CompareFileTime(&first.ftLastWriteTime, &second.ftLastWriteTime);
	return result > 0;
}

static bool cmpByAlphaBet(const WIN32_FIND_DATAA& first, const WIN32_FIND_DATAA& second) {
	return std::string(first.cFileName) < std::string(second.cFileName);
}


static std::string getLongListingFormatString(const FileInfo_s& file, bool humanReadable) {
	std::string str{};
	str += file.isFile ? "-" : "d";
	str += file.attributes + "        ";
	str += humanReadable ? convertToHumanReadable(file.size) : std::to_string(file.size);
	str += "        " + getSystemTimeString(file.time) + "        ";
	str += file.name + "\n";
	return str;
}

static std::string convertToHumanReadable(uint64_t usize) {
	const char* units[] = { "B", "KB", "MB", "GB", "TB", "PB" };
	int unitIndex = 0;
	double size = static_cast<double>(usize);

	while (size >= 1024 && unitIndex < 5) {
		size /= 1024.0;
		++unitIndex;
	}

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << size << units[unitIndex];
	return oss.str();
}

static std::string getSystemTimeString(const SYSTEMTIME& time) {
	return std::to_string(time.wYear) + "-" +
		(time.wMonth < 10 ? "0" : "") + std::to_string(time.wMonth) + "-" +
		(time.wDay < 10 ? "0" : "") + std::to_string(time.wDay) + " " +
		(time.wHour < 10 ? "0" : "") + std::to_string(time.wHour) + ":" +
		(time.wMinute < 10 ? "0" : "") + std::to_string(time.wMinute) + ":" +
		(time.wSecond < 10 ? "0" : "") + std::to_string(time.wSecond);
}
