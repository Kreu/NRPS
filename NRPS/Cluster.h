#include "stdafx.h"

class Module;
class Domain;

class Cluster {
private:
	Sequence sequence_;
	std::string type_;
	std::string id_;
	std::vector<Module*> modules_;
	std::vector<Domain*> domains_;
public:
	Cluster(const std::vector<Feature>& features, const Header& header);
	Cluster(const Feature& feature, const Header& header);
}