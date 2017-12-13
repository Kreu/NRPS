#include "stdafx.h"
#include "File.h"

File::File(const std::string& filename) {
	//If a file is already open
	if (file_.is_open()) {
		throw std::runtime_error("GenBankParser is already associated with a file");
	}

	//If a filename cannot be found
	file_.open(filename);
	if (!file_.is_open()) {
		throw std::runtime_error("Cannot find the file " + filename);
	}

	//Otherwise everything is good
	if (file_.is_open()) {
		std::cout << "Opened " << filename << ".\n";
	}
}

File::File(const char* filename) {
	//If a file is already open
	if (file_.is_open()) {
		throw std::runtime_error("GenBankParser is already associated with a file");
	}

	//If a filename cannot be found
	file_.open(filename);
	if (!file_.is_open()) {
		throw std::runtime_error("Cannot find the file " + std::string(filename));
	}

	//Otherwise everything is good
	if (file_.is_open()) {
		std::cout << "Opened " << filename << ".\n";
	}
}

std::fstream& File::GetFile() {
	return file_;
}

