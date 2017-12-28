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
	bool TESTS_ENABLED = 0;
	if (TESTS_ENABLED) {
		ParserTests::TestAll();
		GenBankParserTests::TestAll();
	}

	std::experimental::filesystem::path path = "C:\\Users\\Valdeko\\source\\repos\\NRPS\\TestSequences";

	int file_count{ 0 };

	for (auto& file : std::experimental::filesystem::directory_iterator(path)) {
		try {
			Parser& parser = GenBankParser(file.path().string());
			std::unique_ptr<Header>& header = parser.GetHeader();
			header->PrintHeaderContent();
			const std::vector<std::unique_ptr<Feature>>& features = parser.GetFeatures();

			for (auto& c : features) {
				c->PrintFeature();
			}

			++file_count;
			std::cout << "Current filecount " << file_count << "\n";
		}
		catch (std::runtime_error& e) {
			std::cout << e.what() << "\n";
		}
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "Execution took " << duration << " milliseconds\n";
    return 0;
}

