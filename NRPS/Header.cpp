#include "stdafx.h"
#include "Header.h"

Header::Header(const std::map<std::string, std::vector<std::string>>& content) {
	mHeaderContent_ = content;
}

Header::Header() {
}

std::map<std::string, std::vector<std::string>>& Header::getHeaderContent() {
	return mHeaderContent_;
}

void Header::clear() {
	mHeaderContent_.clear();
}