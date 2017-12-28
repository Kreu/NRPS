#include "stdafx.h"
#include "GenBankParser.h"
#include "Header.h"
#include "Feature.h"
#include "GenBankFeature.h"

using KeywordSpacer = int;

GenBankParser::GenBankParser(const std::string& filename) : Parser(filename) {
	ParseHeader();
	ParseFeatures();
}

void GenBankParser::ParseHeader() {
	//Extracts the header from a GenBank file.

	//Here is an example of a GenBank file header:

	//LOCUS       SCU49845     5028 bp    DNA             PLN       21-JUN-1999
	//DEFINITION  Saccharomyces cerevisiae TCP1-beta gene, partial cds, and Axl2p
	//(AXL2) and Rev7p (REV7) genes, complete cds.
	//ACCESSION   U49845
	//VERSION     U49845.1  GI:1293613
	//KEYWORDS    .
	//SOURCE      Saccharomyces cerevisiae (baker's yeast)
	//  ORGANISM  Saccharomyces cerevisiae
	//			Eukaryota; Fungi; Ascomycota; Saccharomycotina; Saccharomycetes;
	//			Saccharomycetales; Saccharomycetaceae; Saccharomyces.
	//REFERENCE   1  (bases 1 to 5028)
	//  AUTHORS   Torpey,L.E., Gibbs,P.E., Nelson,J. and Lawrence,C.W.
	//  TITLE     Cloning and sequence of REV7, a gene whose function is required for
	//			DNA damage-induced mutagenesis in Saccharomyces cerevisiae
	//  JOURNAL   Yeast 10 (11), 1503-1509 (1994)
	//  PUBMED    7871890
	//REFERENCE   2  (bases 1 to 5028)
	//  AUTHORS   Roemer,T., Madden,K., Chang,J. and Snyder,M.
	//  TITLE     Selection of axial growth sites in yeast requires Axl2p, a novel
	//			plasma membrane glycoprotein
	//  JOURNAL   Genes Dev. 10 (7), 777-793 (1996)
	//  PUBMED    8846915
	//REFERENCE   3  (bases 1 to 5028)
	//  AUTHORS   Roemer,T.
	//  TITLE     Direct Submission
	//  JOURNAL   Submitted (22-FEB-1996) Terry Roemer, Biology, Yale University, New
	//			Haven, CT, USA

	//A header ends and the next keyword is:
	//FEATURES             Location/Qualifiers

	//The code loops through the file and finds the keywords. It creates a GenBank 
	//object that is a wrapper for all of the data contained within.

	constexpr int HEADER_KEYWORD_WIDTH = 12;

	std::string current_line, header_keyword;
	std::map<std::string, std::vector<std::string>> header_content;
	std::fstream& file = file_.GetStream();

	while (getline(file, current_line)) {
		bool found_header_keyword = false;
	
		//If we hit "FEATURE", this means we are out of the header and need to stop.
		if (current_line.find("FEATURES") != std::string::npos) {
			header_ = std::make_unique<Header>(Header(header_content));
			std::cout << "Hit the end, exiting...\n";
			return;
		}

		//Detect whether the line contains a keyword. The keywords are guaranteed 
		//to be 12 characters and always at the beginning of a line. Easiest way is
		//to grab the first 12 characters and see if it's all spaces or not.
		std::string search_for_keyword = current_line.substr(0, HEADER_KEYWORD_WIDTH);
		if (search_for_keyword.find_first_not_of(' ') != std::string::npos) {
			//Set the flag that we found the keyword
			found_header_keyword = true;
			header_keyword = current_line.substr(0, HEADER_KEYWORD_WIDTH);
			header_keyword.erase(std::remove_if(header_keyword.begin(), header_keyword.end(), isspace), header_keyword.end());

			//Start grabbing the line content past the header keyword width
			std::string line_content{ current_line.substr(HEADER_KEYWORD_WIDTH) };
			header_content[header_keyword].push_back(line_content);
		}

		//If we did not find a header keyword, the next line is part of a multiline
		//comment so we need to append that to the currently tracked header keyword.
		if (!found_header_keyword) {
			std::string line_content{ current_line.substr(12) };
			header_content[header_keyword].push_back(line_content);
		}
	}
};

void GenBankParser::ParseFeatures() {
	//Extracts information about the sequence features from a GenBank file.

	//Sample of features in a file:

	//FEATURES             Location/Qualifiers
	//cluster         1..49384
	//				/clusterblast="2. JKYW01000001_c1	Mycobacterium
	//				tuberculosis MAL020157 adOYz-supercont1.1.C1... (93% of
	//				genes show similarity)"
	//				/clusterblast="3. JKGQ01000001_c1	Mycobacterium
	//				tuberculosis BTB06-001 adOWX-supercont1.1.C1... (93% of
	//				genes show similarity)"
	//				/clusterblast="4. JKFG01000001_c1	Mycobacterium
	//				tuberculosis BTB08-283 adTxx-supercont1.1.C1... (93% of
	//				genes show similarity)"
	//				/clusterblast="5. JJSH01000013_c1	Mycobacterium
	//				tuberculosis NRITLD20 adPad-supercont1.11.C1... (93% of
	//				genes show similarity)"
	//				/clusterblast="6. CP002992_c1	Mycobacterium tuberculosis
	//				CTRI-2, complete genome. (93% of genes show similarity)"
	//				/clusterblast="7. JKFP01000001_c1	Mycobacterium
	//				tuberculosis BTB08-001 adTxi-supercont1.1.C1... (93% of
	//				genes show similarity)"
	//				/clusterblast="8. JKUF01000001_c1	Mycobacterium
	//				tuberculosis TB_RSA87 adOVU-supercont1.1.C1,... (93% of
	//				genes show similarity)"
	//				/clusterblast="9. JKUE01000001_c1	Mycobacterium
	//				tuberculosis TB_RSA88 adOVy-supercont1.1.C1,... (93% of
	//				genes show similarity)"
	//				/clusterblast="10. JKTG01000053_c1	Mycobacterium
	//				tuberculosis TB_RSA113 adOVe-supercont1.7.C... (93% of
	//				genes show similarity)"
	//				/clusterblast="11. JKSG01000017_c1	Mycobacterium
	//				tuberculosis TB_RSA141 adPeA-supercont1.5.C... (93% of
	//				genes show similarity)"
	//				/note="Cluster number: 1"
	//				/note="Detection rule(s) for this cluster type: nrps:
	//				((Condensation & AMP-binding) or (Condensation & A-OX) or
	//				cluster(Condensation,AMP-binding));"
	//				/note="Monomers prediction: (nrp) + (lys-phe)"
	//				/note="Structure image: structures/genecluster1.png"
	//				/product="nrps"
	//gene            49..870
	//				/locus_tag="MT0086"
	//CDS             49..870
	//				/codon_start=1
	//				/db_xref="GI:13879134"
	//				/locus_tag="MT0086"
	//				/note="identified by Glimmer2; putative"
	//				/product="hypothetical protein"
	//				/protein_id="AAK44311.1"
	//				/transl_table=11
	//				/translation="MEPKRSRLVVCAPEPSHAREFPDVAVFSGGRANASQAERLARAVG
	//				RVLADRGVTGGARVRLTMANCADGPTLVQINLQVGDTPLRAQAATAGIDDLRPALIRLD
	//				RQIVRASAQWCPRPWPDRPRRRLTTPAEALVTRRKPVVLRRATPLQAIAAMDAMDYDVH
	//				LFTDAETGEDAVVYRAGPSGLRLARQHHVFPPGWSRCRAPAGPPVPLIVNSRPTPVLTE
	//				AAAVDRAREHGLPFLFFTDQATGRGQLLYSRYDGNLGLITPTGDGVADGLA"


	//TO-DO!!!
	//Instead of having a list of every possible features (which is impossible because
	//people define their own feature types), I am instead detecting whether a line
	//contains a feature and appending it into a dictionary. I have prepopulated it with
	//some features that I know exist in these files.

	//FEATURE_KEYWORDS is a map that contains a list of possible feature keywords
	//encountered in GenBank files. NOT COMPLETE, SEE ABOVE!
	const std::map<std::string, KeywordSpacer> FEATURE_KEYWORDS = { {"cluster", 21},
																	{"gene", 21},
																	{"CDS_motif", 21},
																	{"aSDomain", 21},
																	{"CDS", 21},
																	{"sig_peptide", 21} };
	std::string current_line, foundKeyword;
	std::string currentFeatureContent;
	bool foundFeatureKeyword = false;
	bool foundRightKeyword = false;
	bool parsing_a_feature = false;
	bool in_features_section = false;
	std::fstream& file = file_.GetStream();
	

	while (getline(file, current_line)) {

		//Headers can contain keywords such as "gene" in "Ethanoli\GENE\ns"
		//To avoid parsing error (need to rewrite the parser for this anyway)
		//Do not deal with any lines until we've hit FEATURES which marks the
		//start of where we need to read.
		if (current_line.find("FEATURES") != std::string::npos) {
			in_features_section = true;
		}

		if (!in_features_section) {
			continue;
		}

		//If we hit "ORIGIN", this means we are out of the feature and need to stop.
		//Build the last feature object and quit
		if (current_line.find("ORIGIN") != std::string::npos) {

			feature_content_[foundKeyword].push_back(currentFeatureContent);
			try {
				std::unique_ptr<Feature> p_feature;
				p_feature = std::make_unique<GenBankFeature>(GenBankFeature(feature_content_));
				features_.push_back(std::move(p_feature));
				feature_content_.clear();

				//Set the file stream back to beginning so that it is ready to be used
				//by other funtions.
				file.clear();
				file.seekg(0, std::ios_base::beg);

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
			//20 in the next line is the width of the keyword column before any content starts
			if ((current_line.find(keywords.first) != std::string::npos) && (current_line.find(keywords.first) <= 20)) {

				//If we find a feature keyword but have already been reading in a feature,
				//we need to create a Feature object with all the information available.
				if ((parsing_a_feature == true) && (foundRightKeyword == true)) {
					feature_content_[foundKeyword].push_back(currentFeatureContent);
					try {
						std::unique_ptr<Feature> p_feature;
						p_feature = std::make_unique<GenBankFeature>(GenBankFeature(feature_content_));
						features_.push_back(std::move(p_feature));
						feature_content_.clear();
					}
					catch (const std::invalid_argument& e) {
						std::cout << e.what();
					}
				}

				//If we find a keyword, the next goal is to find out which keyword it is exactly
				//This is because this will match for CDS and CDS_motif, for example. So we need to distinguish
				//between these two options

				//Get the substring that actually represents the keyword in a line
				std::string actualKeyword = current_line.substr(0, 21);
				actualKeyword.erase(std::remove_if(actualKeyword.begin(), actualKeyword.end(), isspace), actualKeyword.end());

				//Need to check the keyword we're comparing against isn't shorter than our unknown, otherwise this operation 
				//isn't safe.
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

				parsing_a_feature = true;
				foundRightKeyword = true;
				foundFeatureKeyword = true;
				currentFeatureContent = current_line.substr(keywords.second);
			}
		}

		//Multi-line header comment
		const std::string STRING_SPACER(" ");
		if ((parsing_a_feature == true) && (foundFeatureKeyword == false)) {
			currentFeatureContent.append(STRING_SPACER);
			currentFeatureContent.append(current_line.substr(FEATURE_KEYWORDS.at(foundKeyword)));
		}
	}
};

const std::vector<std::unique_ptr<Feature>>& GenBankParser::GetFeatures() {
	return features_;
}

std::unique_ptr<Header>& GenBankParser::GetHeader() {
	return header_;
}