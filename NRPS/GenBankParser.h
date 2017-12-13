#pragma once

#include "stdafx.h"
#include "Header.h"
#include "Feature.h"
#include "File.h"

class GenBankParser {
private:
	std::map<std::string, std::vector<std::string>> header_content_;
	std::map<std::string, std::vector<std::string>> feature_content_; //Technically doesn't need to be a vector, as I'm only pushing back one string per Feature
	std::vector<Feature> features_;
	Header header_;
	File file_;

	void ParseFeatures();
	void ParseHeader();
public:
	//ParseFile();
	//ParseFolder();

	GenBankParser::GenBankParser(const std::string& filename);
	Header& GetHeader();
	std::vector<Feature>& GetFeatures();

};

