#include "stdafx.h"
#include "Feature.h"

Feature::~Feature() {};

const std::string& Feature::GetType() {
	return type_;
}

const std::map<std::string, std::vector<std::string>>& Feature::GetContent() {
	return content_;
}

bool Feature::Find(const std::string& qualifier) const {
	if (content_.find(qualifier) != content_.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool Feature::Find(const std::string& qualifier, const std::string& search_term) const {
	if (content_.find(qualifier) != content_.end()) {
		for (const auto& entry : content_.at(qualifier)) {
			if (entry.find(search_term) != std::string::npos) {
				return true;
			}
		}
		return false;
	}
	else {
		return false;
	}
	return false;
}

const std::vector<std::string>& Feature::GetQualifierContent(const std::string& qualifier) {
	if (content_.find(qualifier) != content_.end()) {
		return content_.at(qualifier);
	}
}