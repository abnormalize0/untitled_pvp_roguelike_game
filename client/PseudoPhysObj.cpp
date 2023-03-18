#include "PseudoPhysObj.h"
#include <iostream>

#define MOVEMENT_SPEED 3
#define JUMP_FORCE 60
#define GRAVITY_FORCE 3

#define ON_GROUND 0
#define IN_AIR 1

PseudoPhysObj::PseudoPhysObj() { }

PseudoPhysObj::PseudoPhysObj(float init_x, float init_y, float init_size_x, float init_size_y) {
	x = init_x;
	y = init_y;
	next_x = 0;
	next_y = 0;
	size_x = init_size_x;
	size_y = init_size_y;
	state = ON_GROUND;
}

std::vector<float> PseudoPhysObj::controller() {
	impulse_x = 0;
	impulse_y = 0;
	std::vector<float> impulses;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		impulse_x =  MOVEMENT_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		impulse_x = -1 * MOVEMENT_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		impulse_y = -1 * MOVEMENT_SPEED;
		state = IN_AIR;
	}
	impulses.push_back(impulse_x);
	impulses.push_back(impulse_y);
	return impulses;
}


void PseudoPhysObj::change_parameters(float new_size_x, float new_size_y, float new_pos_x, float new_pos_y) {
	size_x = new_size_x;
	size_y = new_size_y;
	x = new_pos_x;
	y = new_pos_y;
}