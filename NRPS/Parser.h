#pragma once
#include "stdafx.h"
#include "File.h"
#include "Header.h"
#include "Feature.h"

class Parser {
protected:
	File file_;
	std::vector<std::shared_ptr<Feature>> features_;
	std::shared_ptr<Header> header_;
public:
	Parser(const std::string& filename);

	virtual std::shared_ptr<Header>& GetHeader() = 0;
	virtual std::vector<std::shared_ptr<Feature>>& GetAllFeatures() = 0;
	virtual std::vector<std::shared_ptr<Feature>> GetFeatureByType(const std::string& feature_type) = 0;

	virtual ~Parser() = 0;
};