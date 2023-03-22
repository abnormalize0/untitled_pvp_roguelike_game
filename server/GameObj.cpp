#include "GameObj.h"

GameObj::GameObj(float init_x, float init_y, float init_size_x, float init_size_y) {
	x = init_x;
	y = init_y;
	size_x = init_size_x;
	size_y = init_size_y;
}

std::vector<float> GameObj::return_collisions() {
	std::vector<float> parameters;
	parameters.push_back(size_x);
	parameters.push_back(size_y);
	parameters.push_back(x);
	parameters.push_back(y);
	return parameters;
}
