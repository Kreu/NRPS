#pragma once
#include "stdafx.h"

class Feature {
//For testing purposes
friend class GenBankParserTests;

protected:
	std::string type_;
	std::map<std::string, std::vector<std::string>> content_;
	std::map<std::string, std::string> string_content_; //This will be the new content_type, keeping old for compatibility
	int start_location;;
	int stop_location;
public:
	Feature() = default;
	virtual ~Feature() = 0;
	virtual void PrintFeature() = 0;

	const std::string& GetType();
	const std::map<std::string, std::vector<std::string>>& GetContent();
	bool Find(const std::string& qualifier) const;
	bool Find(const std::string& qualifier, const std::string& search_term) const;
	const std::vector<std::string>& Feature::GetQualifierContent(const std::string& qualifier);
};