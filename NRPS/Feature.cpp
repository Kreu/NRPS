#include "stdafx.h"
#include "Feature.h"

Feature::~Feature() {};

const std::string& Feature::GetType() {
	return type_;
}

const std::map<std::string, std::vector<std::string>>& Feature::GetContent() {
	return content_;
}