#include "stdafx.h"
#include "Domain.h"

Domain::Domain(const std::shared_ptr<Feature>& feature) : parent_module_(feature){};