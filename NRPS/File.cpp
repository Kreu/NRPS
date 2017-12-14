#include "stdafx.h"
#include "File.h"

File::File(const std::string& filename) {
	//If a filename cannot be found
	file_.open(filename);
	if (!file_.is_open()) {
		throw std::runtime_error(filename + " cannot be found.")
	}
	//Otherwise everything is good
	else {
		std::cout << "Opened " << filename << ".\n";
	}
}

File::File(const char* filename) {
	//If a filename cannot be found
	file_.open(filename);
	if (!file_.is_open()) {
		throw std::runtime_error(filename + " cannot be found.")
	}
	//Otherwise everything is good
	else {
		std::cout << "Opened " << filename << ".\n";
	}
}

std::fstream& File::GetFile() {
	if (state_ == FILESTATE::OPEN) {
		return file_;
	}
	else {
		std::cout << "File is not in a open state";
	}
}