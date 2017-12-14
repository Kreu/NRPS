#include "stdafx.h"
#include "GenBankParser.h"
#include "Header.h"
#include "Feature.h"

using KeywordSpacer = int;

GenBankParser::GenBankParser(const std::string& filename) : file_(filename) {
	if (file_.GetState() == FILESTATE::OPEN) {
		ParseFeatures();
		ParseHeader();
	}
}

void GenBankParser::ParseHeader() {

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


	std::string currentLine, foundKeyword;
	std::string currentHeaderContent;
	bool foundHeaderKeyword = false;
	bool readingAHeader = false;
	std::fstream& file = file_.GetFile();

	while (getline(file, currentLine)) {

		//If we hit "FEATURE", this means we are out of the header and need to stop.
		if (currentLine.find("FEATURES") != std::string::npos) {
			header_content_[foundKeyword].push_back(currentHeaderContent);
			header_ = Header(header_content_);
			return;
		}

		foundHeaderKeyword = false;

		for (const auto& keywords : HEADER_KEYWORDS) {
			if (currentLine.find(keywords.first) != std::string::npos) {
				//If we find a header keyword but have already been reading in a header,
				//we need to append the previous content into the headerContent map.
				if (readingAHeader == true) {
					header_content_[foundKeyword].push_back(currentHeaderContent);
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

void GenBankParser::ParseFeatures() {

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


	TO-DO!!!

	Instead of having a list of every possible features (which is impossible because
	people define their own feature types), I am instead detecting whether a line
	contains a feature and appending it into a dictionary. I have prepopulated it with
	some features that I know exist in these files.
	*/

	//FEATURE_KEYWORDS is a map that contains a list of possible feature keywords
	//encountered in GenBank files.
	const std::map<std::string, KeywordSpacer> FEATURE_KEYWORDS = { {"cluster", 21},
																	{"gene", 21},
																	{"CDS_motif", 21},
																	{"aSDomain", 21},
																	{"CDS", 21} };
	std::string currentLine, foundKeyword;
	std::string currentFeatureContent;
	bool foundFeatureKeyword = false;
	bool foundRightKeyword = false;
	bool parsingAFeature = false;
	std::fstream& file = file_.GetFile();

	while (getline(file, currentLine)) {

		//If we hit "ORIGIN", this means we are out of the feature and need to stop.
		//Build the last feature object and quit
		if (currentLine.find("ORIGIN") != std::string::npos) {

			feature_content_[foundKeyword].push_back(currentFeatureContent);
			try {
				Feature feature = Feature(feature_content_);
				features_.push_back(feature);
				feature_content_.clear();
				return;
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what();
				return;
			}
			return;
		}

		foundFeatureKeyword = false;

		for (const auto& keywords : FEATURE_KEYWORDS) {
			//std::cout << "Processing " << currentLine << "\n";
			if ((currentLine.find(keywords.first) != std::string::npos) && (currentLine.find(keywords.first) <= 20)) {

				//If we find a feature keyword but have already been reading in a feature,
				//we need to create a Feature object with all the information available.
				if ((parsingAFeature == true) && (foundRightKeyword == true)) {
					//std::cout << "Writing a Feature!\n";
					feature_content_[foundKeyword].push_back(currentFeatureContent);
					try {
						Feature feature = Feature(feature_content_);
						features_.push_back(feature);
						feature_content_.clear();
					}
					catch (const std::invalid_argument& e) {
						std::cout << e.what();
					}
				}

				//std::cout << "Found a keyword " << keywords.first << "\n";

				//If we find a keyword, the next goal is to find out which keyword it is exactly
				//This is because this will match for CDS and CDS_motif, for example. So we need to distinguish
				//between these two options

				//Get the substring that actually represents the keyword in a line
				std::string actualKeyword = currentLine.substr(0, 21);
				actualKeyword.erase(std::remove_if(actualKeyword.begin(), actualKeyword.end(), isspace), actualKeyword.end());

				//Need to check the keyword we're comparing against isn't shorter than our unknown, otherwise this operation 
				//isn't safe.
				//std::cout << "Checking if the two keywords are equal\n";
				if (keywords.first.size() <= actualKeyword.size()) {
					auto result = std::mismatch(keywords.first.begin(), keywords.first.end(), actualKeyword.begin());

					//If the mismatch occurs at a position that is the end of the known keyword, this means the 
					//unknown is longer and is therefore correct. Although it doesn't track the found keywords atm
					//TO-DO
					//If we find a keyword, keep a note of it and compare against that in the next iteration to get
					//the longest possible keyword. For example: CDS, CDS_motif and CDS_motiftype should find
					//CDS_motiftype, but may find CDS_motif instead.

					if ((result.first == keywords.first.end()) && (result.second != actualKeyword.end())) {
						//std::cout << "The actual keyword " << actualKeyword << " is longer than the pattern " << keywords.first << "\n";
						foundRightKeyword = false;
						continue;
					}
					else {
						//But if there isn't a mismatch, we found the correct keyword that has no alternatives.
						foundKeyword = keywords.first;
					}
				}

				//std::cout << "Appending " << currentLine.substr(keywords.second) << " for keyword " << foundKeyword << "\n";
				parsingAFeature = true;
				foundRightKeyword = true;
				foundFeatureKeyword = true;
				currentFeatureContent = currentLine.substr(keywords.second);
			}
		}

		//Multi-line header comment
		const std::string STRING_SPACER(" ");
		if ((parsingAFeature == true) && (foundFeatureKeyword == false)) {
			currentFeatureContent.append(STRING_SPACER);
			currentFeatureContent.append(currentLine.substr(FEATURE_KEYWORDS.at(foundKeyword)));
		}
	}
};

std::vector<Feature>& GenBankParser::GetFeatures() {
	return features_;
}

Header& GenBankParser::GetHeader() {
	return header_;
}