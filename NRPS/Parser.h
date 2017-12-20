#pragma once
#include "stdafx.h"
#include "File.h"
#include "Header.h"
#include "Feature.h"

class Parser {
protected:
	File file_;
	std::vector<std::unique_ptr<Feature>> features_;
	std::unique_ptr<Header> header_;
public:
	Parser(const std::string& filename);

	virtual std::unique_ptr<Header>& GetHeader() = 0;
	virtual const std::vector<std::unique_ptr<Feature>>& GetFeatures() = 0;
	virtual ~Parser() = 0;
};