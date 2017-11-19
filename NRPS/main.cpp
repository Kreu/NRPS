// NRPS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ParserTests.h"
#include "GenBankParserTests.h"
#include "Parser.h"
#include "GenBankParser.h"


int main()
{
	//Run tests
	ParserTests parserTests = ParserTests();
	GenBankParserTests genbankParserTests = GenBankParserTests();
	//parserTests.testAll();
	genbankParserTests.testAll();

	Parser& genBankParser = GenBankParser();
	genBankParser.loadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");

	genBankParser.parseHeader();
	Header& header = genBankParser.getHeader();
	
	genBankParser.parseFeatures();
	std::vector<Feature>& features = genBankParser.getFeatures();

	//for (auto c : header.getHeaderContent()) {
	//	std::cout << c.first << "\n";
	//	for (auto e : c.second) {
	//		std::cout << e << "\n";
	//	}
	//}

	

	int var = 0;
	std::cin >> var;
    return 0;
}

