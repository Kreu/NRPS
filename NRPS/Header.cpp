#include "stdafx.h"
#include "Header.h"

Header::Header(const std::map<std::string, std::vector<std::string>>& content) {
	mHeaderContent_ = content;
}

std::map<std::string, std::vector<std::string>>& Header::getHeaderContent() {
	return mHeaderContent_;
}

void Header::printHeaderContent() {
	for (auto c : mHeaderContent_) {
		std::cout << c.first << ": ";
		for (auto cx : c.second) {
			std::cout << cx << "\n";
		}
	}

}
void Header::clear() {
	mHeaderContent_.clear();
}