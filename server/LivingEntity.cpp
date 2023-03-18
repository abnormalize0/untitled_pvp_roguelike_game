#include "LivingEntity.h"

LivingEntity::LivingEntity(float init_x, float init_y, float init_size_x, float init_size_y) {
	PseudoPhysObj collider(init_x, init_y, init_size_x, init_size_y);
	phys_body = collider;
}


void LivingEntity::game_step(std::vector<sf::IntRect> solid_objects) {
	//phys_body.controller(); //only for player, replace to behavioral_model in next version
	phys_body.physics_process(solid_objects);
}

void LivingEntity::add_impulse(std::vector<float> impulses) {
	phys_body.add_impulses(impulses);
}

std::vector<float> LivingEntity::return_collisions() {
	return phys_body.return_collisions();
}