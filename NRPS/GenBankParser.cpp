#include "stdafx.h"
#include "GenBankParser.h"
#include "Header.h"
#include "Feature.h"

using KeywordSpacer = int;

void GenBankParser::parseHeader() {

	/*
		Extracts the header from a GenBank file.

		Here is an example of a GenBank file header:

		LOCUS       SCU49845     5028 bp    DNA             PLN       21-JUN-1999
		DEFINITION  Saccharomyces cerevisiae TCP1-beta gene, partial cds, and Axl2p
		(AXL2) and Rev7p (REV7) genes, complete cds.
		ACCESSION   U49845
		VERSION     U49845.1  GI:1293613
		KEYWORDS    .
		SOURCE      Saccharomyces cerevisiae (baker's yeast)
		  ORGANISM  Saccharomyces cerevisiae
					Eukaryota; Fungi; Ascomycota; Saccharomycotina; Saccharomycetes;
					Saccharomycetales; Saccharomycetaceae; Saccharomyces.
		REFERENCE   1  (bases 1 to 5028)
		  AUTHORS   Torpey,L.E., Gibbs,P.E., Nelson,J. and Lawrence,C.W.
		  TITLE     Cloning and sequence of REV7, a gene whose function is required for
					DNA damage-induced mutagenesis in Saccharomyces cerevisiae
		  JOURNAL   Yeast 10 (11), 1503-1509 (1994)
		  PUBMED    7871890
		REFERENCE   2  (bases 1 to 5028)
		  AUTHORS   Roemer,T., Madden,K., Chang,J. and Snyder,M.
		  TITLE     Selection of axial growth sites in yeast requires Axl2p, a novel
					plasma membrane glycoprotein
		  JOURNAL   Genes Dev. 10 (7), 777-793 (1996)
		  PUBMED    8846915
		REFERENCE   3  (bases 1 to 5028)
		  AUTHORS   Roemer,T.
		  TITLE     Direct Submission
		  JOURNAL   Submitted (22-FEB-1996) Terry Roemer, Biology, Yale University, New
					Haven, CT, USA

		A header ends and the next keyword is:
		FEATURES             Location/Qualifiers

		The code loops through the file and finds the keywords. It creates a GenBank 
		object that is a wrapper for all of the data contained within.
	*/

	const std::string STRING_SPACER(" ");
	const std::map<std::string, KeywordSpacer> HEADER_KEYWORDS = { {"LOCUS", 12},
															  	   {"DEFINITION", 12},
																   {"ACCESSION", 12},
																   {"VERSION", 12},
																   {"KEYWORDS", 12},
																   {"SOURCE", 12},
																   {"ORGANISM", 12},
																   {"REFERENCE", 12},
																   {"AUTHORS", 10},
																   {"TITLE", 10},
																   {"JOURNAL", 10},
																   {"PUBMED", 10} };

	//Keep in case I make it back into an array
	//const std::array<std::string, 12> HEADER_KEYWORDS = {"LOCUS",
	//													"DEFINITION",
	//													"ACCESSION",
	//													"VERSION", 
	//													"KEYWORDS",
	//													"SOURCE",
	//													"ORGANISM",
	//													"REFERENCE",
	//													"AUTHORS",
	//													"TITLE",
	//													"JOURNAL",
	//													"PUBMED",};

	if (!file.is_open()) {
		std::cout << "GenBankParser does not have a file associated with it, please load a file using loadFile().\n";
		return;
	}

	std::string currentLine, foundKeyword;
	std::string currentHeaderContent;
	bool foundHeaderKeyword = false;
	bool readingAHeader = false;

	while (getline(file, currentLine)) {

		//If we hit "FEATURE", this means we are out of the header and need to stop.
		if (currentLine.find("FEATURES") != std::string::npos) {
			mHeaderContent_[foundKeyword].push_back(currentHeaderContent);

			try {
				mHeader_ = Header(mHeaderContent_);
				/*mHeaderContent_.clear();*/
				return;
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what();
				return;
			}
			return;
		}

		foundHeaderKeyword = false;

		for (const auto& keywords : HEADER_KEYWORDS) {
			if (currentLine.find(keywords.first) != std::string::npos) {
				//If we find a header keyword but have already been reading in a header,
				//we need to append the previous content into the headerContent map.
				if (readingAHeader == true) {
					mHeaderContent_[foundKeyword].push_back(currentHeaderContent);
				}

				//Keep track of the keyword we found
				foundKeyword = keywords.first;

				readingAHeader = true;
				foundHeaderKeyword = true;
				currentHeaderContent = currentLine.substr(keywords.second);
			}
		}

		//Multi-line header comment
		if ((readingAHeader == true) && (foundHeaderKeyword == false)) {
			currentHeaderContent.append(STRING_SPACER);
			currentHeaderContent.append(currentLine.substr(HEADER_KEYWORDS.at(foundKeyword)));
		}
	}
};

void GenBankParser::parseFeatures() {

	//TO-DO
	//Every feature line that starts with '/' needs to be put into a separate
	//container because they contain various different annotations about the
	//file in question.


	/*
	Extracts information about the sequence features from a GenBank file.

	Sample of features in a file:

	FEATURES             Location/Qualifiers
	cluster         1..49384
					/clusterblast="2. JKYW01000001_c1	Mycobacterium
					tuberculosis MAL020157 adOYz-supercont1.1.C1... (93% of
					genes show similarity)"
					/clusterblast="3. JKGQ01000001_c1	Mycobacterium
					tuberculosis BTB06-001 adOWX-supercont1.1.C1... (93% of
					genes show similarity)"
					/clusterblast="4. JKFG01000001_c1	Mycobacterium
					tuberculosis BTB08-283 adTxx-supercont1.1.C1... (93% of
					genes show similarity)"
					/clusterblast="5. JJSH01000013_c1	Mycobacterium
					tuberculosis NRITLD20 adPad-supercont1.11.C1... (93% of
					genes show similarity)"
					/clusterblast="6. CP002992_c1	Mycobacterium tuberculosis
					CTRI-2, complete genome. (93% of genes show similarity)"
					/clusterblast="7. JKFP01000001_c1	Mycobacterium
					tuberculosis BTB08-001 adTxi-supercont1.1.C1... (93% of
					genes show similarity)"
					/clusterblast="8. JKUF01000001_c1	Mycobacterium
					tuberculosis TB_RSA87 adOVU-supercont1.1.C1,... (93% of
					genes show similarity)"
					/clusterblast="9. JKUE01000001_c1	Mycobacterium
					tuberculosis TB_RSA88 adOVy-supercont1.1.C1,... (93% of
					genes show similarity)"
					/clusterblast="10. JKTG01000053_c1	Mycobacterium
					tuberculosis TB_RSA113 adOVe-supercont1.7.C... (93% of
					genes show similarity)"
					/clusterblast="11. JKSG01000017_c1	Mycobacterium
					tuberculosis TB_RSA141 adPeA-supercont1.5.C... (93% of
					genes show similarity)"
					/note="Cluster number: 1"
					/note="Detection rule(s) for this cluster type: nrps:
					((Condensation & AMP-binding) or (Condensation & A-OX) or
					cluster(Condensation,AMP-binding));"
					/note="Monomers prediction: (nrp) + (lys-phe)"
					/note="Structure image: structures/genecluster1.png"
					/product="nrps"
	gene            49..870
					/locus_tag="MT0086"
	CDS             49..870
					/codon_start=1
					/db_xref="GI:13879134"
					/locus_tag="MT0086"
					/note="identified by Glimmer2; putative"
					/product="hypothetical protein"
					/protein_id="AAK44311.1"
					/transl_table=11
					/translation="MEPKRSRLVVCAPEPSHAREFPDVAVFSGGRANASQAERLARAVG
					RVLADRGVTGGARVRLTMANCADGPTLVQINLQVGDTPLRAQAATAGIDDLRPALIRLD
					RQIVRASAQWCPRPWPDRPRRRLTTPAEALVTRRKPVVLRRATPLQAIAAMDAMDYDVH
					LFTDAETGEDAVVYRAGPSGLRLARQHHVFPPGWSRCRAPAGPPVPLIVNSRPTPVLTE
					AAAVDRAREHGLPFLFFTDQATGRGQLLYSRYDGNLGLITPTGDGVADGLA"


	Instead of having a list of every possible features (which is impossible because 
	people define their own feature types), I am instead detecting whether a line 
	contains a feature and appending it into a dictionary. I have prepopulated it with
	some features that I know exist in these files.
	*/

	if (!file.is_open()) {
		std::cout << "GenBankParser does not have a file associated with it, please load a file using loadFile().\n";
		return;
	}

	const std::string STRING_SPACER(" ");
	
	//FEATURE_KEYWORDS is a map that contains a list of possible feature keywords
	//encountered in GenBank files.
	const std::map<std::string, KeywordSpacer> FEATURE_KEYWORDS = { {"cluster", 21},
																    {"gene", 21},
																    {"CDS", 21},
																    {"aSDomain", 21},
																    {"CDS_motif", 21} };

	std::string currentLine, foundKeyword;
	std::string currentFeatureContent;
	bool foundFeatureType = false;
	bool readingAFeature = false;

	while (getline(file, currentLine)) {

		//If we hit "ORIGIN", this means we are out of the feature and need to stop.
		//Build the last feature object and quit
		if (currentLine.find("ORIGIN") != std::string::npos) {

			mFeatureContent_[foundKeyword].push_back(currentFeatureContent);
			try {
				Feature feature = Feature(mFeatureContent_);
				mFeatures_.push_back(feature);
				mFeatureContent_.clear();
				return;
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what();
				return;
			}
			return;
		}

		foundFeatureType = false;

		//Find the correct keyword that matches
		for (const auto& keywords : FEATURE_KEYWORDS) {

			//This comparison needs to make sure it matches the longest substring, and not just every Feature type
			//For example, "CDS_motif" matches "CDS" and creates a wrong Feature object out of it
			std::regex pattern(keywords.first);
			std::smatch matches;

			if (std::regex_search (currentLine, matches, pattern)) {
				std::cout << "Following matches were found:\n";
				for (auto c : matches) {
					std::cout << c << "\n";
				}
			}

			if ((currentLine.find(keywords.first) != std::string::npos) && (currentLine.find(keywords.first) <= 20)) {
				//Check that the keyword we found isn't actually part of a longer keyword
				//for (const auto& kwds : FEATURE_KEYWORDS) {
				//	//Make sure the second string is larger than first string, otherwise the mismatch will be an invalid pointer.
				//	//if (kwds.first.size() >= keywords.first.size()) {
				//	//	auto result = std::mismatch(keywords.first.begin(), keywords.first.end(), kwds.first.begin());
				//	//	if (result.first == keywords.first.end()) {
				//	//		std::cout << "Found " << kwds.first << " in " << keywords.first << "\n";
				//	//	}
				//	//}



				///*	if (currentLine.find(k.first) > matchPosition)) {
				//	std::cout << "Was " << keywords.first << ", now is " << k.first << "\n";
				//		foundKeyword = k.first;
				//	}*/
				//}				

				//If we find a feature keyword but have already been reading in a feature,
				//we need to create a Feature object with all the information available.
				if (readingAFeature == true) {
					mFeatureContent_[foundKeyword].push_back(currentFeatureContent);

					try {
						Feature feature = Feature(mFeatureContent_);
						mFeatureContent_.clear();
					}
					catch (const std::invalid_argument& e) {
						std::cout << e.what();
					}
					
				}

				//Keep track of the feature keyword that we found
				foundKeyword = keywords.first;

				readingAFeature = true;
				foundFeatureType = true;
				currentFeatureContent = currentLine.substr(keywords.second);
			}
		}

		//Multi-line header comment
		if ((readingAFeature == true) && (foundFeatureType == false)) {
			currentFeatureContent.append(STRING_SPACER);
			currentFeatureContent.append(currentLine.substr(FEATURE_KEYWORDS.at(foundKeyword)));
		}
	}
};

std::vector<Feature>& GenBankParser::getFeatures() {
	return mFeatures_;
}

Header& GenBankParser::getHeader() {
	return mHeader_;
}

FileState GenBankParser::closeFile() {
	//When closing a file, we need to reset all members.
	if (file.is_open()) {
		mHeaderContent_.clear();
		mFeatureContent_.clear();
		mFeatures_.clear();
		mHeader_.clear();

		file.close();
		std::cout << "Closed open file.\n";
		return CLOSED;
	}
	else {
		std::cout << "A file is not currently open.\n";
		return NOFILEOPEN;
	}
}
