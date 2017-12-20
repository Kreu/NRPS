#pragma once
#include "stdafx.h"

class Feature {
//For testing purposes
friend class GenBankParserTests;

protected:
	std::string type_;
	std::map<std::string, std::vector<std::string>> content_;
	int start_location;;
	int stop_location;
public:
	Feature() = default;
	virtual ~Feature() = 0;

	virtual void PrintFeature() = 0;
};