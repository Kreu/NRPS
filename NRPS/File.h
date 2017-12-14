#pragma once
#include "stdafx.h"

enum class FILESTATE { OPEN, CLOSED };

class File {
private:
	std::fstream file_;
	FILESTATE state_;
public:
	File(const std::string& filename);
	File(const char* filename);
	std::fstream& GetFile();

	FILESTATE GetState();
};