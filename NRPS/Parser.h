#pragma once
#include "stdafx.h"

enum FileState { OPEN, CLOSED, FILEALREADYOPEN, FILEMISSING, NOFILEOPEN };

class Parser {
protected:
	std::ifstream file;

public:
	FileState loadFile(const std::string&);
	FileState closeFile();

	virtual void parseFeatures() = 0;
	virtual void parseHeader() = 0;

	virtual ~Parser();

};

