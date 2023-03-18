#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class PseudoPhysObj {
private:
	float x;
	float y;
	float size_x;
	float size_y;
	float next_x;
	float next_y;

	float air_friction = 1.1;
	float ground_friction = 1.2;

	float impulse_x = 0.0;
	float impulse_y = 0.0;

	int state;
public:
	PseudoPhysObj();
	PseudoPhysObj(float init_x, float init_y, float init_size_x, float init_size_y);
	std::vector<float> controller();
	float get_x() { return x; }
	float get_y() { return y; }
	void change_parameters(float new_size_x, float new_size_y, float new_pos_x, float new_pos_y);
};