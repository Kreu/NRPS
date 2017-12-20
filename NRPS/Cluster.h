#include "stdafx.h"
//#include "Sequence.h"

class Module;
class Domain;
class Feature;
class Header;


class Cluster {
private:
	//Sequence sequence_;
	std::string type_;
	std::string id_;
	std::vector<Module*> modules_;
	std::vector<Domain*> domains_;

	void ConstructHeader(const Header& header);
	void ConstructFeature(const std::vector<Feature>& features);
	void ConstructFeature(const Feature& feature);

public:
	Cluster(const std::vector<Feature>& features, const Header& header);
	Cluster(const Feature& feature, const Header& header);
};