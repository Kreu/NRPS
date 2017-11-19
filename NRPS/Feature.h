#pragma once

#include "stdafx.h"

class Feature {
private:
	std::string mFeatureType_;
	std::vector<std::string> mFeatureContents_;
public:
	Feature(const std::map<std::string, std::vector<std::string>>&);
	void printFeature();
};