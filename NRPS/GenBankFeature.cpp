#include "stdafx.h"
#include "GenBankFeature.h"

GenBankFeature::GenBankFeature(const std::map<std::string, std::vector<std::string>>& feature_content) {
	//TO-DO
	//Write the constructor to unpack the map and populate the fields with appropriate values

	//Feature constructor expects a map that has one key whose value corresponds
	//to a Feature type (e.g. CDS, gene, etc). The key value is a vector of strings
	//that contains each line of the original record file as a separate string
	//For example, the following feature:
	//gene            29559..31544
	//				  /locus_tag = "MT0111"
	//would produce a map with the key "gene" and a vector with two strings, "29559..31544" and "/locus_tag = "MT0111"

	//Check that the map contains only one key
	//If it doesn't, the passed map is not correct for Feature construction as no Feature has multiple types
	if (feature_content.size() != 1) {
		throw std::invalid_argument("Map contains too many keys, cannot construct Feature object");
	}

	UnpackFeatureContent(feature_content);
};

void GenBankFeature::PrintFeature() {
	std::cout << "Type: " << type_ << "\n";
	std::cout << "Location " << start_location << " to " << stop_location << "\n";
	for (const auto& c : content_) {
		std::cout << "Content: " << c.first << "\n";
		for (auto a : c.second) {
			if (c.second.size() > 1) {
				std::cout << a << ", ";
			}
			else {
				std::cout << a;
			}
		}
		std::cout << "\n";
	}
}

void GenBankFeature::UnpackFeatureContent(const std::map<std::string, std::vector<std::string>>& content) {
	//Unpack the map and create a map. The keys are feature types, and the values are strings
	//For example:
	//  /asDomain_id = "nrpspksdomains_MT0110_Xdom03"
	//	/database = "nrpspksdomains.hmm"
	//	/detection = "hmmscan"
	//Would create a map with three keys "asDomain_id", "database" and "detection" with values
	//of "nrpspksdomains_MT0110_Xdom03", "nrpspksdomains.hmm" and "hmmscan", respectively. 

	for (const auto& k : content) {
		type_ = k.first;

		std::smatch matches;
		//Matches the sequence location of the features, e.g. "23411..23699"
		std::regex codonLocation("(\\d+)\\.{2}(\\d+)");
		//Matches the qualifiers within features, e.g. "/asDomain_id="hmmscan"" becomes "asDomain_id"
		std::regex feature("(\\/.*?)(?:\\s|$)(?=\\/|$)");

		std::regex qualifierType("(?:\\/)(\\w*)(?=\=\")");
		std::regex qualifierContent("(?:\=\")(.*?)(?=\")"); //(?:\=\")(.*?)(?=\") is the non-C++ malarkey version

		for (const auto& line : k.second) {
			
			//TO-DO
			//Actually add the codon location
			if (std::regex_search(line, matches, codonLocation)) {
				start_location = std::stoi(matches.str(1));
				stop_location = std::stoi(matches.str(2));
			}

			bool foundFeatureContent = false;
			bool foundFeatureType = false;

			for (auto it = std::sregex_iterator(line.begin(), line.end(), feature); it != std::sregex_iterator(); ++it) {
				std::string matchedString = it->str();
				foundFeatureContent = false;
				foundFeatureType = false;
				std::string qualifierContentString, qualifierTypeString;

				if (std::regex_search(matchedString, matches, qualifierType)) {
					qualifierTypeString = matches.str(1);
					foundFeatureType = true;
				}

				if (std::regex_search(matchedString, matches, qualifierContent)) {
					qualifierContentString = matches.str(1);
					foundFeatureContent = true;
				}

				if (foundFeatureContent == true && foundFeatureType == true) {
					//Need to format the "translation" string because it comes with spaces
					//in the string.
					if (qualifierTypeString == "translation") {
						qualifierContentString.erase(remove_if(qualifierContentString.begin(), qualifierContentString.end(), isspace), qualifierContentString.end());
					}
					content_[qualifierTypeString].push_back(qualifierContentString);
				}

			}

		}
	}
}