#include "stdafx.h"
#include "Cluster.h"

Cluster::Cluster(const std::vector<Feature>& features, const Header& header) {
	Cluster.ConstructHeader(header);
	Cluster.ConstructFeature(features);
}

Cluster::Cluster(const Feature& feature, const Header& header) {
	Cluster.ConstructHeader(header);
	Cluster.ConstructFeature(feature);
}

void Cluster::ConstructHeader(const Header& header) {
	
}

void Cluster::ConstructFeature(const std::vector<Feature>& features) {

}
