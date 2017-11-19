#pragma once
#include "stdafx.h"

enum FileState { OPEN, CLOSED, FILEALREADYOPEN, FILEMISSING, NOFILEOPEN };

class Header;
class Feature;

class Parser {
protected:
	std::ifstream file;

public:
	FileState loadFile(const std::string&);
	virtual FileState closeFile();

	virtual void parseFeatures() = 0;
	virtual void parseHeader() = 0;
	virtual Header& getHeader() = 0;
	virtual std::vector<Feature>& getFeatures() = 0;
	virtual ~Parser();

};

