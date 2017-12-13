// NRPS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "ParserTests.h"
//#include "GenBankParserTests.h"
#include "GenBankParser.h"


int main()
{
	//Run tests
	//ParserTests parserTests = ParserTests();
	//GenBankParserTests genbankParserTests = GenBankParserTests();
	//parserTests.testAll();
	//genbankParserTests.testAll();

	GenBankParser genBankParser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");

	Header& header = genBankParser.GetHeader();
	header.printHeaderContent();
	
	std::vector<Feature>& features = genBankParser.GetFeatures();

	for (auto c : features) {
		c.printFeature();
	}

	int var = 0;
	std::cin >> var;
    return 0;
}

