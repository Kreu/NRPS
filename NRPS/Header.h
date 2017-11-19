#pragma once
#include "stdafx.h"

class Header {
private:
	std::map<std::string, std::vector<std::string>> mHeaderContent_;
public:
	Header();
	Header(const std::map<std::string, std::vector<std::string>>&);

	std::map<std::string, std::vector<std::string>>& getHeaderContent();

	void clear();
};