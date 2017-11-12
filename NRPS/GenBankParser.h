#pragma once
#include "stdafx.h"

class Parser;
class Feature;
class Header;

class GenBankParser : public Parser {
private:
	std::vector<std::string> headerContent; //make this into a map later
	std::map<std::string, std::vector<std::string>> mFeatureContent;
	std::vector<Feature> mFeatures;
	Header mHeader;

public:
	virtual void parseFeatures();
	virtual void parseHeader();
	std::vector<Feature>& getFeatures();
	virtual Header& getHeader();

	GenBankParser() {};
};

