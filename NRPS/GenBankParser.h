#pragma once

#include "stdafx.h"
#include "Parser.h"
#include "Header.h"
#include "Feature.h"

class GenBankParser : public Parser {
private:
	std::map<std::string, std::vector<std::string>> header_content_;
	std::map<std::string, std::vector<std::string>> feature_content_;
	void ParseFeatures();
	void ParseHeader();
public:
	GenBankParser(const std::string& filename);
	virtual ~GenBankParser() = default;
	std::unique_ptr<Header>& GetHeader();
	const std::vector<std::unique_ptr<Feature>>& GetFeatures();
};

