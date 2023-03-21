#include "SolidObj.h"

SolidObj::SolidObj() {}

SolidObj::SolidObj(float init_x, float init_y, float init_size_x, float init_size_y) {
	x = init_x;
	y = init_y;
	size_x = init_size_x;
	size_y = init_size_y;
}

sf::IntRect SolidObj::get_collision() {
	sf::IntRect collision(x, y, size_x, size_y);
	return collision;
}