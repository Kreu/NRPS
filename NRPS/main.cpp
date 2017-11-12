// NRPS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	//Run tests
	ParserTests parserTests = ParserTests();
	GenBankParserTests genbankParserTests = GenBankParserTests();
	parserTests.testAll();
	genbankParserTests.testAll();

	Parser& genBankParser = GenBankParser();
	genBankParser.loadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");
	genBankParser.parseHeader();
	genBankParser.parseFeatures();

	int var = 0;
	std::cin >> var;
    return 0;
}

