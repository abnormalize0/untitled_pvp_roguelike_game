#include "PseudoPhysObj.h"
#include <iostream>

#define MOVEMENT_SPEED 15
#define JUMP_FORCE 70
#define GRAVITY_FORCE 5

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
	//impulse_x = 0;
	//impulse_y = 0;
	std::vector<float> impulses;
	if (button_states[1]) {
		impulse_x = MOVEMENT_SPEED;
	}
	if (button_states[0]) {
		impulse_x = -1 * MOVEMENT_SPEED;
	}
	if ((button_states[2])&&(state == ON_GROUND)&&(jump_lock)) {
		jump_lock = 0;
		impulse_y = -1 * JUMP_FORCE;
		state = IN_AIR;
	}
	if ((!button_states[2]) && (state == ON_GROUND) && (!jump_lock)) {
		jump_lock = 1;
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

void PseudoPhysObj::physics_process(std::vector<sf::IntRect> solid_objects) {
	next_x = x;
	next_y = y;
	impulse_y = impulse_y + GRAVITY_FORCE;
	if (impulse_x != 0) {
		next_x = x + impulse_x;
	}
	if (impulse_y != 0) {
		float temp_i = impulse_y;
		next_y = y + impulse_y;
	}
	if (state) {
		impulse_x = impulse_x / air_friction;
		impulse_y = impulse_y / air_friction;
	} else {
		impulse_x = impulse_x / ground_friction;
		impulse_y = impulse_y / ground_friction;
	}
	resolve_collisions(solid_objects);
	if (y == next_y) {
		state = ON_GROUND;
	}
	x = next_x;
	y = next_y;
}

void PseudoPhysObj::resolve_collisions(std::vector<sf::IntRect> solid_objects) {
	sf::IntRect hitbox1(next_x, next_y, size_x, size_y);
	sf::IntRect hitbox2(x, next_y, size_x, size_y);
	sf::IntRect hitbox3(next_x, y, size_x, size_y);
	for (int i = 0; i < solid_objects.size(); i++) {
		if (hitbox1.intersects(solid_objects[i])) {
			if (!(hitbox2.intersects(solid_objects[i]))) {
				precise_position_x(solid_objects[i]);
				impulse_x = 0;
			}
			if (!(hitbox3.intersects(solid_objects[i]))) {
				precise_position_y(solid_objects[i]);
				impulse_y = 0;
			}
			if ((hitbox2.intersects(solid_objects[i])) && (hitbox3.intersects(solid_objects[i]))) {
				precise_position_x(solid_objects[i]);
				precise_position_y(solid_objects[i]);
				impulse_x = 0;
				impulse_y = 0;
			}
		}
	}
}

void PseudoPhysObj::precise_position_x(sf::IntRect collision) {
	int limit = JUMP_FORCE;
	int step;
	float precise;
	if (x > next_x) {
		step = -1;
		precise = x;
	} else {
		step = 1;
		precise = x;
	}
	while (limit > 0) {
		sf::IntRect hitbox(precise + step, next_y, size_x, size_y);
		if (hitbox.intersects(collision)) {
			next_x = precise;
			return;
		}
		precise = precise + step;
		limit--;
	}
}

void PseudoPhysObj::precise_position_y(sf::IntRect collision) {
	int limit = JUMP_FORCE;
	int step;
	float precise;
	if (y > next_y) {
		step = -1;
		precise = y;
	} else {
		step = 1;
		precise = y;
	}
	while (limit > 0) {
		sf::IntRect hitbox(next_x, precise + step, size_x, size_y);
		if (hitbox.intersects(collision)) {
			next_y = precise;
			return;
		}
		precise = precise + step;
		limit--;
	}
}

void PseudoPhysObj::change_button_state(int button) {
	if (button > 0) {
		button_states[abs(button) - 1] = 1;
	} else {
		button_states[abs(button) - 1] = 0;
	}
}