#pragma once

#include "stdafx.h"
#include "Header.h"
#include "Feature.h"
#include "File.h"

enum FileState { OPEN, CLOSED, FILEALREADYOPEN, FILEMISSING, NOFILEOPEN };

class GenBankParser {
private:
	std::map<std::string, std::vector<std::string>> mHeaderContent_;
	std::map<std::string, std::vector<std::string>> mFeatureContent_; //Technically doesn't need to be a vector, as I'm only pushing back one string per Feature
	std::vector<Feature> mFeatures_;
	Header mHeader_;

	File file_;

public:
	GenBankParser::GenBankParser(const std::string& filename);

	void ParseFeatures();
	void ParseHeader();

	Header& GetHeader();
	std::vector<Feature>& GetFeatures();

	FileState CloseFile();
};

