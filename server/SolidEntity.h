#pragma once

#include "SolidObj.h"

class SolidEntity {
private:
	SolidObj solid_body;
public:
	SolidEntity(float init_x, float init_y, float init_size_x, float init_size_y);
	sf::IntRect return_rect();
	std::vector<float> return_collisions();
};

