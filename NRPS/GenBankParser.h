#pragma once

#include "stdafx.h"

#include "Header.h"
#include "Parser.h"
#include "Feature.h"

class GenBankParser : public Parser {
private:
	std::map<std::string, std::vector<std::string>> mHeaderContent_;
	std::map<std::string, std::vector<std::string>> mFeatureContent_;
	std::vector<Feature> mFeatures_;
	Header mHeader_;
public:
	virtual void parseFeatures();
	virtual void parseHeader();
	virtual FileState closeFile();
	virtual Header& getHeader();
	virtual std::vector<Feature>& getFeatures();

	GenBankParser() {};
};

