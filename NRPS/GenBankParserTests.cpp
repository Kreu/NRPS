#include "stdafx.h"
#include <cassert>
#include "Parser.h"
#include "GenBankParser.h"
#include "GenBankParserTests.h"

void GenBankParserTests::TestParseHeader() {

	//Test with real input
	try {
		Parser& parser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");

		std::unique_ptr<Header>& header = parser.GetHeader();
		std::map<std::string, std::vector<std::string>>& expectedHeaderContent = header->GetHeaderContent();

		std::vector<std::string> locusContent = expectedHeaderContent["LOCUS"];
		assert(locusContent[0] == "AE000516               49384 bp    DNA              UNK 01-JAN-1980");

		std::vector<std::string> defContent = expectedHeaderContent["DEFINITION"];
		assert(defContent[0] == "Mycobacterium tuberculosis CDC1551, complete genome.");

		std::vector<std::string> accContent = expectedHeaderContent["ACCESSION"];
		assert(accContent[0] == "AE000516");

		std::vector<std::string> verContent = expectedHeaderContent["VERSION"];
		assert(verContent[0] == "AE000516.2");

		std::vector<std::string> keyContent = expectedHeaderContent["KEYWORDS"];
		assert(keyContent[0] == ".");

		std::vector<std::string> srcContent = expectedHeaderContent["SOURCE"];
		assert(srcContent[0] == ".");

		std::vector<std::string> orgContent = expectedHeaderContent["ORGANISM"];
		assert(orgContent[0] == ". .");
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
	}

	//Test a manually edited file with random junk in it
	try {
		Parser& parser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile2.gbk");
		std::unique_ptr<Header>& header = parser.GetHeader();
		std::map<std::string, std::vector<std::string>>& expectedHeaderContent = header->GetHeaderContent();

		std::vector<std::string> locusContent = expectedHeaderContent["LOCUS"];
		assert(locusContent[0] == "ABC123456 10540bp LOLDNA    UNK 01-JAN-1980");

		std::vector<std::string> defContent = expectedHeaderContent["DEFINITION"];
		assert(defContent[0] == "Totally a real genome");

		std::vector<std::string> accContent = expectedHeaderContent["ACCESSION"];
		assert(accContent[0] == "ABC123456");

		std::vector<std::string> verContent = expectedHeaderContent["VERSION"];
		assert(verContent[0] == "ABC123456.12345");

		std::vector<std::string> keyContent = expectedHeaderContent["KEYWORDS"];
		assert(keyContent[0] == "HMM");

		std::vector<std::string> srcContent = expectedHeaderContent["SOURCE"];
		assert(srcContent[0] == "E. coli");

		std::vector<std::string> orgContent = expectedHeaderContent["ORGANISM"];
		assert(orgContent[0] == "E.coli and Sf9");
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
	}
}


template <typename Map>
bool map_compare(Map const &lhs, Map const &rhs) {
	// No predicate needed because there is operator== for pairs already.
	return lhs.size() == rhs.size()
		&& std::equal(lhs.begin(), lhs.end(),
			rhs.begin());
}

void GenBankParserTests::TestParseFeatures() {
	//Test files are set up to contain a header, ONE feature, and origin.

	//Test for "CDS" Feature
	try {
		Parser& parser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestFeatureCDS.gbk");
		const std::vector<std::unique_ptr<Feature>>& features = parser.GetFeatures();

		for (auto& c : features) {
			assert(c->type_ == "CDS");

			//This is what the content_ should be
			std::map<std::string, std::vector<std::string>> expected_content {
				//{ "codon_start", std::vector<std::string>{"1"} },
				{ "db_xref", std::vector<std::string>{"GI:13879158"} },
				{ "locus_tag", std::vector<std::string>{"MT0111"} },
				{ "note", std::vector<std::string>{"identified by similarity to EGAD:32940"} },
				{ "product", std::vector<std::string>{"conserved hypothetical protein"} },
				{ "protein_id", std::vector<std::string>{"AAK44333.1"} },
				//{ "transl_table", std::vector<std::string>{"11"} },
				{ "translation", std::vector<std::string>{"MGTHGATKSATSAVPTPRSNSMAMVRLAIGLLGVCAVVAAFGLVSGARRYAEAGNPYPGAFVSVAEPVGFFAASLAGALCLGALIHVVMTAKPEPDGLIDAAAFRIHLLAERVSGLWLGLAATMVVIQAAHDTGVGPARLLASGALSDSVAASEMARGWIVAAICALVVATALRLYTRWLGHVVLLVPTVLAVVATAVTGNPGQGPDHDYATSAAIVFAVAFATLTGLKIAAALAGTTPSRAVLVTQVTCGALALAYGAMLLYLFIPGWAVDSDFARLGLLAGVILTSVWLFDCWRLLVRPPHAGRRRGGGSGAALAMMAAMASIAAMAVMTAPRFLTHAFTAWDVFLGYELPQPPTIARVLTVWRFDSLIGAAGVVLAIGYAAGFAALRRRGNSWPVGRLIAWLTGCAALVFTSGSGVRAYGSAMFSVHMAEHMTLNMFIPVLLVLGGPVTLALRVLPVTGDGRPPGAREWLTWLLHSRVTTFLSHPITAFVLFVASPYIVYFTPLFDTFVRYHWGHEFMAIHFLVVGYLFYWAIIGIDPGPRRLPYPGRIGLLFAVMPFHAFFGIALMTMSSTVGATFYRSVNLPWLSSIIADQHLGGGIAWSLTELPVIMVIVALVTQWARQDRRVASREDRHADSDYADDELEAYNAMLRELSRMRR"} }
			};

			assert(c->content_ == expected_content);
		}
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
	}

	//Test for "aSDomain" Feature
	try {
		Parser& parser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestFeatureAsdomain.gbk");
		const std::vector<std::unique_ptr<Feature>>& features = parser.GetFeatures();

		for (auto& c : features) {
			//This is what the content_ should be
			std::map<std::string, std::vector<std::string>> expected_content {
				//{ "codon_start", std::vector<std::string>{"1"} },
				{ "asDomain_id", std::vector<std::string>{"nrpspksdomains_MT0110_Xdom03"} },
				{ "database", std::vector<std::string>{"nrpspksdomains.hmm"} },
				{ "detection", std::vector<std::string>{"hmmscan"} },
				{ "domain", std::vector<std::string>{"TD"} },
				{ "evalue", std::vector<std::string>{"1.30E-85"} },
				{ "locus_tag", std::vector<std::string>{"MT0110"} },
				{ "score", std::vector<std::string>{"278.1"} },
				{ "translation", std::vector<std::string>{"VLLTGATGFLGRYLVLELLRRLDVDGRLICLVRAESDEDARRRLEKTFDSGDPELLRHFKELAADRLEVVAGDKSEPDLGLDQPMWRRLAETVDLIVDSAAMVNAFPYHELFGPNVAGTAELIRIALTTKLKPFTYVSTADVGAAIEPSAFTEDADIRVISPTRTVDGGWAGGYGTSKWAGEVLLREANDLCALPVAVFRCGMILADTSYAGQLNMSDWVTRMVLSLMATGIAPRSFYEPDSEGNRQRAHFDGLPVTFVAEAIA"} }
			};

			assert(c->type_ == "aSDomain");
			assert(c->content_ == expected_content);
		}
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
	}


	//Test for "gene" Feature
	try {
		Parser& parser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestFeatureGene.gbk");
		const std::vector<std::unique_ptr<Feature>>& features = parser.GetFeatures();

		for (auto& c : features) {
			//This is what the content_ should be
			std::map<std::string, std::vector<std::string>> expected_content {
				{ "locus_tag", std::vector<std::string>{"MT0111"} },
			};

			assert(c->type_ == "gene");
			assert(c->content_ == expected_content);
		}
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
	}
}

void GenBankParserTests::TestAll() {
	TestParseHeader();
	TestParseFeatures();
}