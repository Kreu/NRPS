#pragma once
#include "stdafx.h"

class Parser;
class Feature;

class GenBankParser : public Parser {
private:
	std::vector<std::string> headerContent; //make this into a map later
	std::map<std::string, std::vector<std::string>> featureContent;
	std::vector<Feature> features;
public:
	virtual void parseFeatures();
	virtual void parseHeader();

	GenBankParser() {};
};

