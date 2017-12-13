#pragma once
#include "stdafx.h"

enum class FILESTATE { OPEN, CLOSED, FILE_ALREADY_OPEN, FILE_MISSING, NO_FILE_OPEN };

class File {
private:
	std::fstream file_;
	FILESTATE Open(const std::string& filename);
	FILESTATE Close();
public:
	File(const std::string& filename);
	File(const char* filename);
	std::fstream& GetFile();
};