#include "stdafx.h"

Feature::Feature(const std::map<std::string, std::vector<std::string>>& featureContent) {
	//TO-DO
	//Write the constructor

	//Check that the map contains only one key
	if (featureContent.size() != 1) {
		throw std::invalid_argument("Map contains too many keys, cannot construct Feature object");

	}


	//Unpack the map
	for (auto& k : featureContent) {
		featureType = k.first;

		std::cout << k.first << "\n";
		for (auto& line : k.second) {
			std::cout << line << "\n";
		}
		std::cout << "---------------------------------------------" << "\nDone with a FEATURE\n" <<
			"---------------------------------------------\n";
	}


};