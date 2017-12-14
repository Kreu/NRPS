#include "stdafx.h"
#include "File.h"

File::File(const std::string& filename) {
	//If a filename cannot be found
	file_.open(filename);
	if (!file_.is_open()) {
		state_ = FILESTATE::CLOSED;
		std::cout << filename << " cannot be found.\n";
	}

	//Otherwise everything is good
	else {
		state_ = FILESTATE::OPEN;
		std::cout << "Opened " << filename << ".\n";
	}
}

File::File(const char* filename) {
	//If a filename cannot be found
	file_.open(filename);
	if (!file_.is_open()) {
		state_ = FILESTATE::CLOSED;
		std::cout << filename << " cannot be found.\n";
	}

	//Otherwise everything is good
	else {
		state_ = FILESTATE::OPEN;
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

FILESTATE File::GetState() {
	return state_;
}