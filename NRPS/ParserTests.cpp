#include "stdafx.h"
//#include <cassert>
//#include "GenBankParser.h"
//#include "ParserTests.h"
//
//
////Tests for loadFile()
//void ParserTests::testLoadFileNotFound() {
//	Parser& parser = GenBankParser();
//	//Try opening a file while specifying no filename
//	assert(parser.loadFile("") == FILEMISSING);
//	//Try opening a file that does not exist
//	assert(parser.loadFile("FileDoesNotExist.txt") == FILEMISSING);
//}
//
//void ParserTests::testLoadFileFileAlreadyOpen() {
//	Parser& parser = GenBankParser();
//	//Try loading a file into a parser when there is a file already open
//	parser.loadFile("C:/Users/Valdeko/source/repos/NRPS/Debug/TestParser.txt");
//	assert(parser.loadFile("C:/Users/Valdeko/source/repos/NRPS/Debug/TestParser.txt") == FILEALREADYOPEN);
//}
//
//void ParserTests::testLoadFileOpenARealFile() {
//	Parser& parser = GenBankParser();
//	//Try opening a file that does exist
//	assert(parser.loadFile("C:/Users/Valdeko/source/repos/NRPS/Debug/TestParser.txt") == OPEN);
//}
//
//
////Test for closeFile()
//void ParserTests::testcloseFileNoFileIsOpen() {
//	Parser& parser = GenBankParser();
//	//Try closing a file when no file is opened
//	assert(parser.closeFile() == NOFILEOPEN);
//}
//
//void ParserTests::testcloseFileCloseAnOpenFile() {
//	Parser& parser = GenBankParser();
//	//Try closing a file that has been opened
//	parser.loadFile("C:/Users/Valdeko/source/repos/NRPS/Debug/TestParser.txt");
//	assert(parser.closeFile() == CLOSED);
//}
//
//void ParserTests::testAll() {
//	testLoadFileNotFound();
//	testLoadFileFileAlreadyOpen();
//	testLoadFileOpenARealFile();
//
//	testcloseFileNoFileIsOpen();
//	testcloseFileCloseAnOpenFile();
//}