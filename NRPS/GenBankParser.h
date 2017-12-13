#pragma once

#include "stdafx.h"

#include "Header.h"
#include "Parser.h"
#include "Feature.h"

enum FileState { OPEN, CLOSED, FILEALREADYOPEN, FILEMISSING, NOFILEOPEN };

class GenBankParser {
private:
	std::map<std::string, std::vector<std::string>> mHeaderContent_;
	std::map<std::string, std::vector<std::string>> mFeatureContent_; //Technically doesn't need to be a vector, as I'm only pushing back one string per Feature
	std::vector<Feature> mFeatures_;
	Header mHeader_;

	std::ifstream file;

public:
	GenBankParser() {};

	FileState LoadFile(const std::string&);
	FileState CloseFile();

	void parseFeatures();
	void parseHeader();
	FileState closeFile();
	Header& getHeader();
	std::vector<Feature>& getFeatures();
};

