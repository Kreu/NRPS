#include "stdafx.h"
#include "File.h"
//
//File::File(const std::string& filename) {
//	if (this->Open(filename) != FILESTATE::OPEN) {
//		this->~File();
//	}
//}

//FILESTATE File::Open(const std::string& filename) {
//	//Check that we do not currently have a file open
//	if (file_.is_open()) {
//		std::cout << "A file is already open.\n";
//		return FILESTATE::FILE_ALREADY_OPEN;
//	}
//
//	//If not, open the file
//	std::cout << "Loading " << filename << ".\n";
//	file_.open(filename);
//	if (file_.is_open()) {
//		std::cout << "Opened " << filename << ".\n";
//		return FILESTATE::OPEN;
//	}
//	//If we can't open the file
//	else {
//		std::cout << filename << " could not be opened.\n";
//		return FILESTATE::NO_FILE_OPEN;
//	}
//}

//FILESTATE File::Close() {
//	if (file_.is_open()) {
//		file_.close();
//		std::cout << "Closed open file.\n";
//		return FILESTATE::CLOSED;
//	}
//	else {
//		std::cout << "A file is not currently open.\n";
//		return FILESTATE::NO_FILE_OPEN;
//	}
////}
//
//std::fstream& File::GetFile() {
//	return file_;
//}
//
