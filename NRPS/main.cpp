// NRPS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "ParserTests.h"
//#include "GenBankParserTests.h"

#include "GenBankParser.h"
#include "Header.h"
#include "Feature.h"
#include "GenBankFeature.h"

//Include for testing purposes
#include "ParserTests.h"
#include "GenBankParserTests.h"

int main()
{
	//Run tests
	bool TESTS_ENABLED = 0;
	if (TESTS_ENABLED) {
		ParserTests parserTests = ParserTests();
		parserTests.TestAll();

		GenBankParserTests genbankParserTests = GenBankParserTests();
		genbankParserTests.TestAll();
	}

	try {
		Parser& parser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");
		std::unique_ptr<Header>& header = parser.GetHeader();
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

