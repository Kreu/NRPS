#pragma once
#include "stdafx.h"
#include "File.h"

class Feature;
class Header;

class Parser {
protected:
	File file_;
	std::vector<Feature*> features_;
	Header& header_;
public:
	virtual Header& GetHeader() = 0;
	virtual std::vector<Feature*> GetFeatures() = 0;
	~Parser() = 0;
}