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
	auto t1 = std::chrono::high_resolution_clock::now();

	//Run tests
	bool TESTS_ENABLED = 1;
	if (TESTS_ENABLED) {
		ParserTests::TestAll();
		GenBankParserTests::TestAll();
	}

	std::experimental::filesystem::path path = "C:\\Users\\Valdeko\\Desktop\\BGC_downloader\\TestSequences";
	//std::experimental::filesystem::path path = "C:\\Users\\Valdeko\\source\\repos\\NRPS\\Sequences";
	//std::experimental::filesystem::path path = "C:\\Users\\Valdeko\\source\\repos\\NRPS\\Tests";

	std::vector<std::shared_ptr<Feature>> CDS_features;

	for (auto& file : std::experimental::filesystem::directory_iterator(path)) {
		try {
			Parser& parser = GenBankParser(file.path().string());
			//std::shared_ptr<Header>& header = parser.GetHeader();
			//header->PrintHeaderContent();
			CDS_features = parser.GetFeatureByType("CDS");
		}
		catch (std::runtime_error& e) {
			std::cout << e.what() << "\n";
		}
	}

	for (const auto& feat : CDS_features) {
		feat->PrintFeature();
	}


	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "Execution took " << duration << " milliseconds\n";
    return 0;
}

