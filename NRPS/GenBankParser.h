#pragma once
#include "stdafx.h"
#include "Parser.h"

class GenBankParser : public Parser {
private:
	std::vector<std::string> headerContent; //make this into a map later
	std::vector<std::string> featureContent; //make this into a map later
public:
	virtual void parseFeatures();
	virtual void parseHeader();

	GenBankParser() {};
};

