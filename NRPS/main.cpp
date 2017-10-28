// NRPS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	//Run tests
	ParserTests parserTests = ParserTests();
	//parserTests.testAll();

	Parser& genBankParser = GenBankParser();
	genBankParser.loadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\AE000516.2.cluster001.gbk");
	genBankParser.parseHeader();
	genBankParser.parseFeatures();

	int var = 0;
	std::cin >> var;
    return 0;
}

