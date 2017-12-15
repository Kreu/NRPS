#pragma once
#include "stdafx.h"

class File;

class Parser {
protected:
	File file_;
	std::vector<Feature*> features_;
	Header& header_;
public:
	virtual Header& GetHeader();
	virtual std::vector<Feature*> GetFeatures();
	~Parser() = 0;
}