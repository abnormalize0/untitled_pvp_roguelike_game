#include "SolidObj.h"

SolidObj::SolidObj() {}

SolidObj::SolidObj(float init_x, float init_y, float init_size_x, float init_size_y) {
	x = init_x;
	y = init_y;
	size_x = init_size_x;
	size_y = init_size_y;
}

sf::IntRect SolidObj::get_rect() {
	sf::IntRect collision(x, y, size_x, size_y);
	return collision;
}


std::vector<float> SolidObj::return_collisions() {
	std::vector<float> parameters;
	parameters.push_back(size_x);
	parameters.push_back(size_y);
	parameters.push_back(x);
	parameters.push_back(y);
	return parameters;
}