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
	//ParserTests parserTests = ParserTests();
	//GenBankParserTests genbankParserTests = GenBankParserTests();
	//parserTests.testAll();
	//genbankParserTests.testAll();

	GenBankParser genBankParser = GenBankParser();
	genBankParser.LoadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");

	genBankParser.parseHeader();
	Header& header = genBankParser.getHeader();
	header.printHeaderContent();
	
	genBankParser.parseFeatures();
	std::vector<Feature>& features = genBankParser.getFeatures();

	//for (auto c : features) {
	//	c.printFeature();
	//}

	int var = 0;
	std::cin >> var;
    return 0;
}

