#include "stdafx.h"
#include "Feature.h"

Feature::Feature(const std::map<std::string, std::vector<std::string>>& featureContent) {
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
	if (featureContent.size() != 1) {
		throw std::invalid_argument("Map contains too many keys, cannot construct Feature object");
	}

	//Unpack the map
	for (const auto& k : featureContent) {
		mFeatureType_ = k.first;
		for (const auto& line : k.second) {
			mFeatureContents_.push_back(line);
		}
	}
};

void Feature::printFeature() {
	std::cout << "\nFeature type: " << mFeatureType_ << "\n";
	for (const auto& c : mFeatureContents_) {
		std::cout << c << "\n";
	}
}