#pragma once

#include <SFML/Graphics.hpp>

class GameObj {
private:
	float x;
	float y;
	float size_x;
	float size_y;
public:
	GameObj(float init_x, float init_y, float init_size_x, float init_size_y);
	std::vector<float> return_collisions();
};