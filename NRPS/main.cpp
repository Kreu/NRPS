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
	const bool TESTS_ENABLED = 0;
	if (TESTS_ENABLED) {
		ParserTests::TestAll();
		GenBankParserTests::TestAll();
	}

	std::experimental::filesystem::path path = "C:\\Users\\Valdeko\\Desktop\\BGC_downloader\\TestSequences";
	//std::experimental::filesystem::path path = "C:\\Users\\Valdeko\\source\\repos\\NRPS\\Sequences";
	//std::experimental::filesystem::path path = "C:\\Users\\Valdeko\\source\\repos\\NRPS\\Tests";

	for (auto& file : std::experimental::filesystem::directory_iterator(path)) {
		try {
			Parser& parser = GenBankParser(file.path().string());
			std::vector<std::shared_ptr<Feature>> modules, domains;
			std::vector<std::shared_ptr<Feature>> CDS_features = parser.GetFeatureByType("CDS");

			//Find all 'modules' which are CDS features that have been marked biosynthetic
			for (const auto& feat : CDS_features) {
				if (feat->Find("sec_met", "Kind: biosynthetic")) {
					modules.push_back(std::move(feat));
				}
			}
			//Find all 'domains' which are aSDomain features.
			std::vector<std::shared_ptr<Feature>> aSDomains = parser.GetFeatureByType("aSDomain");
			for (const auto& feat : aSDomains) {
				domains.push_back(std::move(feat));
			}

			for (const auto& feat : modules) {
				auto tag_content = feat->GetQualifierContent("locus_tag");

			}
			//for (const auto& feat : modules) {
			//	auto tag_content = feat->GetQualifierContent("locus_tag");
			//	for (const auto& tag : tag_content) {
			//		domains.push_back(std::move(feat));
			//	}
			//}



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

