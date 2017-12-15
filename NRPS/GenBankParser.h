#pragma once

#include "stdafx.h"
#include "Header.h"
#include "Feature.h"
#include "File.h"

class GenBankParser : public Parser {
private:
	std::map<std::string, std::vector<std::string>> header_content_;
	std::map<std::string, std::vector<std::string>> feature_content_;

	void ParseFeatures();
	void ParseHeader();
public:
	GenBankParser(const std::string& filename);
	Header& GetHeader();
	std::vector<Feature*>& GetFeatures();
};

