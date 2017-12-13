#pragma once

#include "stdafx.h"

#include "Header.h"
#include "Parser.h"
#include "Feature.h"

class GenBankParser : public Parser {
private:
	std::map<std::string, std::vector<std::string>> mHeaderContent_;
	std::map<std::string, std::vector<std::string>> mFeatureContent_; //Technically doesn't need to be a vector, as I'm only pushing back one string per Feature
	std::vector<Feature> mFeatures_;
	Header mHeader_;
public:
	GenBankParser() {};
	virtual void parseFeatures();
	virtual void parseHeader();
	virtual FileState closeFile();
	virtual Header& getHeader();
	virtual std::vector<Feature>& getFeatures();
};

