#pragma once
#include "stdafx.h"

namespace GenBank {
class Header {
private:
	std::map<std::string, std::vector<std::string>> mHeaderContent_;
public:
	Header() {};
	explicit Header(const std::map<std::string, std::vector<std::string>>&);

	std::map<std::string, std::vector<std::string>>& getHeaderContent();
	void printHeaderContent();

	void clear();
};
}