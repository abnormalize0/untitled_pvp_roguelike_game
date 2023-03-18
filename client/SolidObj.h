#pragma once

#include <SFML/Graphics.hpp>

class SolidObj {
private:
	float x;
	float y;
	float size_x;
	float size_y;
public:
	SolidObj();
	SolidObj(float init_x, float init_y, float init_size_x, float init_size_y);
	sf::IntRect get_collision();
};