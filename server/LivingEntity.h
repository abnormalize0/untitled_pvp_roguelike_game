#pragma once

#include <vector>
#include "PseudoPhysObj.h"

class LivingEntity {
private:
	PseudoPhysObj phys_body;
public:
	LivingEntity(float init_x, float init_y, float init_size_x, float init_size_y);
	void game_step(std::vector<sf::IntRect>);
	void add_impulse(std::vector<float> impulses);
	std::vector<float> return_collisions();
};

