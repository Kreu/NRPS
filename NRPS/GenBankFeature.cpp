#include "stdafx.h"
#include "GenBankFeature.h"

GenBankFeature::GenBankFeature(const std::map<std::string, std::vector<std::string>>& feature_content) {
	//Feature constructor expects a map that has one key whose value corresponds
	//to a Feature type (e.g. CDS, gene, etc). The key value is a vector of strings
	//that contains each line of the original record file as a separate string
	//For example, the following feature:
	//gene            29559..31544
	//				  /locus_tag = "MT0111"
	//would produce a map with the key "gene" and a vector with "/locus_tag = "MT0111".

	//Check that the map contains only one key.
	//If it doesn't, the passed map is not correct for Feature construction as no Feature has multiple types.
	if (feature_content.size() != 1) {
		throw std::invalid_argument("Map contains too many keys, cannot construct Feature object\n");
	}
	else {
		UnpackFeatureContent(feature_content);
		FixTranslationField();
	}
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
				std::cout << a << "\n";
				break;
			}
		}
		
	}
}

void GenBankFeature::UnpackFeatureContent(const std::map<std::string, std::vector<std::string>>& content) {
	//Unpack the map and create a map. The keys are feature types, and the values are strings
	//For example:
	//  asDomain_id = "nrpspksdomains_MT0110_Xdom03"
	//	database = "nrpspksdomains.hmm"
	//	detection = "hmmscan"
	//Would create a map with three keys "asDomain_id", "database" and "detection" with values
	//of "nrpspksdomains_MT0110_Xdom03", "nrpspksdomains.hmm" and "hmmscan", respectively. 
	
	std::smatch matches;
	//Matches the sequence location of the features, e.g. "23411..23699".
	//Doesn't take into account if the location is complement or something
	//weird, just finds numbers. It's fine for antiSMASH database though.
	std::regex codon_location("(\\d+)\\.{2}(\\d+)");

	bool feature_location_found = false;
	bool multiline_comment = false;

	for (const auto& k : content) {
		type_ = k.first;

		size_t type_content_delimiter_pos{ 0 };
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
				//If the line does not contain a '=', it is not a real qualifier.
				if (line.find('=') == std::string::npos) {
					//If we find a line with / and no =, it is part of a multiline
					//comment that just happens to have / at the beginning, for
					//example:
					// /product="alkyl hydroperoxide reductase, F52a subunit, FAD
					// /NAD(P) - binding"
					if (multiline_comment) {
						qualifier_content = RemoveQuotationMarks(line);
						content_[qualifier_type].push_back(qualifier_content);
					}
					else {
						//The line is not important. Probably.
						continue;
					}
				}

				auto type_and_content = GetTypeAndContent(line);
				qualifier_type = type_and_content.first;
				qualifier_content = type_and_content.second;

				//Content of the qualifier between the '"' '"' characters
				//Check whether the last character is a '"'. If it is not, then
				//have a multi-line comment.
				if (line.back() == '"') {
					multiline_comment = false;
					qualifier_content = RemoveQuotationMarks(qualifier_content);
					content_[qualifier_type].push_back(qualifier_content);
				}
				else {
					multiline_comment = true;
					qualifier_content = RemoveQuotationMarks(qualifier_content);
					content_[qualifier_type].push_back(qualifier_content);
					continue;
				}
			}

			if (multiline_comment) {

				if (line.back() == '"') {
					//Remove the quotation mark from the end.
					qualifier_content = RemoveQuotationMarks(line);
					content_[qualifier_type].push_back(qualifier_content);
					multiline_comment = false;
				}
				//If line doesn't end with '"', there is more to come!
				else {
					qualifier_content = line;
					content_[qualifier_type].push_back(qualifier_content);
				}
			}
		}
	}
}

std::string GenBankFeature::RemoveQuotationMarks(const std::string& line) {
	//Removes quotation marks around a string. Only removes the first and last
	//quotation mark, it does not touch multiple ones. For example, 
	//'"This is an example string"' becomes 'This is an example' string, but
	//'""I have two quotation marks!"' becomes '"I have to quotation marks'.

	std::string modified_string;
	if ((line.front() == '"') && (line.back() == '"')) {
		modified_string = line.substr(1, line.size() - 2);
		return modified_string;
	}

	if (!(line.front() == '"') && (line.back() == '"')) {
		modified_string = line.substr(0, line.size() - 1);
		return modified_string;
	}

	if ((line.front() == '"') && !(line.back() == '"')) {
		modified_string = line.substr(1, line.size());
		return modified_string;
	}
	else {
		return line;
	}
}

std::pair<std::string, std::string> GenBankFeature::GetTypeAndContent(const std::string& line) {

	//Takes a Qualifier line such as "/protein_id="BAI29479.1"" and separates 
	//it into feature type and content as first and second members of the pair. 
	//In this case first would be "protein_id" and second would be ""BAI29479.1""

	//Get the location of the '=' as this is the delimiter for
	//the qualifier type and qualifier content.
	size_t type_content_delimiter_pos{ 0 };
	type_content_delimiter_pos = line.find_first_of('=');

	//Take off 1 from the end because we don't want the position of
	//the '='. We also don't want the first ('/') character.
	std::string qualifier_type = line.substr(1, type_content_delimiter_pos - 1);

	//Content is everything from the '=' character onwards.
	std::string qualifier_content = line.substr(type_content_delimiter_pos + 1);

	std::pair<std::string, std::string> type_and_content;
	return type_and_content = std::make_pair(qualifier_type, qualifier_content);
}