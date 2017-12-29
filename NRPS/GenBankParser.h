#pragma once

#include "stdafx.h"
#include "Parser.h"
#include "Header.h"
#include "Feature.h"

class GenBankParser : public Parser {
private:
	void ParseFeatures();
	void ParseHeader();
public:
	GenBankParser(const std::string& filename);
	virtual ~GenBankParser() override = default;

	std::unique_ptr<Header>& GetHeader();
	const std::vector<std::unique_ptr<Feature>>& GetFeatures();
};

