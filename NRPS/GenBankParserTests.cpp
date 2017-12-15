#include "stdafx.h"
//#include <cassert>
//#include "Parser.h"
//#include "GenBankParser.h"
//#include "GenBankParserTests.h"
//
//
////Tests for loadFile()
//void GenBankParserTests::testParseHeader() {
//	std::cout << "Testing testParseHeader()\n";
//	Parser& parser = GenBankParser();
//
//	//Test with real input
//	parser.loadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");
//	parser.parseHeader();
//
//	Header& header = parser.getHeader();
//	std::map<std::string, std::vector<std::string>>& expectedHeaderContent = header.getHeaderContent();
//
//	std::vector<std::string> locusContent = expectedHeaderContent["LOCUS"];
//	assert(locusContent[0] == "AE000516               49384 bp    DNA              UNK 01-JAN-1980");
//
//	std::vector<std::string> defContent = expectedHeaderContent["DEFINITION"];
//	assert(defContent[0] == "Mycobacterium tuberculosis CDC1551, complete genome.");
//
//	std::vector<std::string> accContent = expectedHeaderContent["ACCESSION"];
//	assert(accContent[0] == "AE000516");
//
//	std::vector<std::string> verContent = expectedHeaderContent["VERSION"];
//	assert(verContent[0] == "AE000516.2");
//
//	std::vector<std::string> keyContent = expectedHeaderContent["KEYWORDS"];
//	assert(keyContent[0] == ".");
//
//	std::vector<std::string> srcContent = expectedHeaderContent["SOURCE"];
//	assert(srcContent[0] == ".");
//
//	std::vector<std::string> orgContent = expectedHeaderContent["ORGANISM"];
//	assert(orgContent[0] == ". .");
//
//
//	////Test a manually edited file with random junk in it
//	parser.closeFile();
//	parser.loadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile2.gbk");
//	parser.parseHeader();
//
//	locusContent = expectedHeaderContent["LOCUS"];
//	assert(locusContent[0] == "ABC123456 10540bp LOLDNA    UNK 01-JAN-1980");
//
//	defContent = expectedHeaderContent["DEFINITION"];
//	assert(defContent[0] == "Totally a real genome");
//
//	accContent = expectedHeaderContent["ACCESSION"];
//	assert(accContent[0] == "ABC123456");
//
//	verContent = expectedHeaderContent["VERSION"];
//	assert(verContent[0] == "ABC123456.12345");
//
//	keyContent = expectedHeaderContent["KEYWORDS"];
//	assert(keyContent[0] == "HMM");
//
//	srcContent = expectedHeaderContent["SOURCE"];
//	assert(srcContent[0] == "E. coli");
//
//	orgContent = expectedHeaderContent["ORGANISM"];
//	assert(orgContent[0] == "E.coli and Sf9");
//
//	std::cout << "Passed all GenBankParserTests::testParseHeader() tests\n";
//}
//
//void GenBankParserTests::testParseFeatures() {
//	std::cout << "Testing testParseFeatures()\n";
//	Parser& parser = GenBankParser();
//	parser.loadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");
//	parser.parseFeatures();
//}
//
//void GenBankParserTests::testAll() {
//	testParseHeader();
//	testParseFeatures();
//}