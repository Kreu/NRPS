#pragma once

#include "stdafx.h"

class Feature {
private:
	std::string mFeatureType_;
	std::map<std::string, std::vector<std::string>> mFeatureContent_;
	int mFeatureStartLocation_;
	int mFeatureStopLocation_;

	void unpackFeatureContent(const std::map<std::string, std::vector<std::string>>&);
public:
	Feature(const std::map<std::string, std::vector<std::string>>&);
	void printFeature();
};