#include "stdafx.h"
#include "Parser.h"

Parser::~Parser() {

}

FileState Parser::loadFile(const std::string& filename) {
	//Check that we do not currently have a file open
	if (file.is_open()) {
		std::cout << "A file is already open.\n";
		return FILEALREADYOPEN;
	}

	std::cout << "Loading " << filename << ".\n";
	file.open(filename);

	if (file.is_open()) {
		std::cout << "Opened " << filename << ".\n";
		return OPEN;
	}
	else {
		std::cout << filename << " could not be located.\n";
		return FILEMISSING;
	}
}

FileState Parser::closeFile() {
	if (file.is_open()) {
		file.close();
		std::cout << "Closed open file.\n";
		return CLOSED;
	}
	else {
		std::cout << "A file is not currently open.\n";
		return NOFILEOPEN;
	}
}



