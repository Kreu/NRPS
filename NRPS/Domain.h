#pragma once
#include "stdafx.h"
#include "Feature.h"

class Domain {
private:
	const std::shared_ptr<Feature>& parent_module_;
public:
	explicit Domain(const std::shared_ptr<Feature>& feature);
	~Domain() = default;
};

