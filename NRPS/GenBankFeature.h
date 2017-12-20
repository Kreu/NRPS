#pragma once
#include "stdafx.h"
#include "Feature.h"

class GenBankFeature : public Feature {
private:
	void UnpackFeatureContent(const std::map<std::string, std::vector<std::string>>& content);
public:
	GenBankFeature(const std::map<std::string, std::vector<std::string>>& feature_content);
	~GenBankFeature() = default;
	void PrintFeature();
};