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
	//would produce a map with the key "gene" and a vector with "/locus_tag = "MT0111"

	//Check that the map contains only one key
	//If it doesn't, the passed map is not correct for Feature construction as no Feature has multiple types
	if (feature_content.size() != 1) {
		throw std::invalid_argument("Map contains too many keys, cannot construct Feature object\n");
	}

	UnpackFeatureContent(feature_content);
	FixTranslationField();
};

void GenBankFeature::FixTranslationField() {
	//This is required because the translation field should be one long string rather than multiple single strings.
	if (content_.find("translation") != content_.end()) {
		std::string fixed_string;
		for (auto& content : this->content_["translation"]) {
			fixed_string = fixed_string + content;
		}
		this->content_["translation"].clear();
		this->content_["translation"].push_back(fixed_string);
	}
}
void GenBankFeature::PrintFeature() {
	std::cout << "[" << type_ << "]\n";
	std::cout << "\t" << start_location << " to " << stop_location << "\n";
	for (const auto& c : content_) {
		std::cout << "\t" << c.first << ": ";

		for (auto a : c.second) {
			if (c.second.size() > 1) {
				std::cout << "\t" << a << "\n";
			}
			else {
				std::cout << "" << a << "\n";
				break;
			}
		}
		
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
	
	//Define the regex-es to find features
	std::smatch matches;
	//Matches the sequence location of the features, e.g. "23411..23699"
	std::regex codon_location("(\\d+)\\.{2}(\\d+)");

	bool feature_location_found = false;
	bool parsing_a_feature = false;
	bool multiline_comment = false;

	for (const auto& k : content) {
		type_ = k.first;
		//std::cout << type_ << "\n";
		
		size_t qualifier_type_end_pos{ 0 };
		std::string qualifier_content, qualifier_type;

		for (const auto& line : k.second) {

			//If the line starts with a '/', it is a qualifier. Therefore I need to extract
			//the qualifier type and the content to finish constructing a Feature.
			//For example, in the following qualifier 
			// /asDomain_id="nrpspksdomains_MT0110_Xdom03"
			//I need to extract asDomain_id as the qualifier type, and
			//"nrpspksdomains_MT0110_Xdom03" as qualifier content.
			//The '=' will serve as the delimiting character.

			//Once we've found the location, we don't need to look for it again.
			if (feature_location_found == false) {
				if (std::regex_search(line, matches, codon_location)) {
					start_location = std::stoi(matches.str(1));
					stop_location = std::stoi(matches.str(2));
					feature_location_found = true;
				}
			}

			//If the '/' character is at the first position in the line, it usually
			//indicates a new qualifier.
			if ((line.find_first_of('/') != std::string::npos) && (line.find_first_of('/') == 0)) {
				//std::cout << line << "\n";
				//If the line does not contain a '=', it is not a real qualifier
				//and should be discarded.
				if (line.find('=') == std::string::npos) {
					std::cout << "Discarding " << line << "\n";
					continue;
				}

				//Get the location of the '=' as this is the delimiter for
				//the qualifier type and qualifier content
				qualifier_type_end_pos = line.find_first_of('=');

				//Take off 1 from the end because we don't want the position of
				//the '='. We also don't want the first ('/') character.
				qualifier_type = line.substr(1, qualifier_type_end_pos - 1);

				//Content of the qualifier between the '"' '"' characters
				//Check whether the last character is a '"'. If it is not, then
				//have a multi-line comment
				if (line.back() == '"') {
					multiline_comment = false;
					//Remove quotes around the string and add to the map.
					//It's +1 because we don't want the '=' character we just found.
					qualifier_content = line.substr(qualifier_type_end_pos + 1);
					if ((qualifier_content.front() == '"') && (qualifier_content.back() == '"')) {
						//Remove the first and last character, e.g. the quotation marks
						qualifier_content = qualifier_content.substr(1, qualifier_content.size() - 2);
						content_[qualifier_type].push_back(qualifier_content);
						//std::cout << qualifier_content << "\n";
					}

				}
				else {
					qualifier_content = line.substr(qualifier_type_end_pos + 1);
					//If there is '"' at the beginning of the string, add a
					//spacer of 2 characters, otherwise add 1.
					if (qualifier_content.front() == '"') {
						qualifier_content = line.substr(qualifier_type_end_pos + 2);
					}
					else {
						qualifier_content = line.substr(qualifier_type_end_pos + 1);
					}
					content_[qualifier_type].push_back(qualifier_content);
					multiline_comment = true;
					continue;
				}
				//It's +1 because we don't want the '=' character we just found.
				//qualifier_content = line.substr(qualifier_type_end_pos + 1);
				//std::cout << qualifier_content << "\n";

				//If all checks have passed, add it to the content_ map
				//content_[qualifier_type].push_back(qualifier_content);

				parsing_a_feature = true;
			}


			//If it is a multiline comment
			if (multiline_comment) {
				//If line doesn't end with '"', there is more to come!
				if (line.back() == '"') {
					qualifier_content = line.substr(0, line.size() -  1);
					//std::cout << qualifier_content << "\n";
					content_[qualifier_type].push_back(qualifier_content);
					multiline_comment = false;
				}
				else {
					//std::cout << line << "\n";
					qualifier_content = line;
					content_[qualifier_type].push_back(qualifier_content);
				}
			}
		}
	}
}