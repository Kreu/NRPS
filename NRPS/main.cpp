// NRPS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "ParserTests.h"
//#include "GenBankParserTests.h"

#include "GenBankParser.h"
#include "Header.h"
#include "Feature.h"
#include "GenBankFeature.h"

int main()
{
	//Run tests
	//ParserTests parserTests = ParserTests();
	//GenBankParserTests genbankParserTests = GenBankParserTests();
	//parserTests.testAll();
	//genbankParserTests.testAll();

	try {
		Parser& parser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");
		std::unique_ptr<Header>& header = parser.GetHeader();
		header->PrintHeaderContent();
		const std::vector<std::unique_ptr<Feature>>& features = parser.GetFeatures();

		for (auto& c : features) {
			c->PrintFeature();
		}
	}
	catch (std::runtime_error& e) {
		std::cout << e.what() << "\n";
	}

    return 0;
}

