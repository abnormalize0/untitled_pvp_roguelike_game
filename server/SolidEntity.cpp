#include "SolidEntity.h"

SolidEntity::SolidEntity(float init_x, float init_y, float init_size_x, float init_size_y) {
	SolidObj collider(init_x, init_y, init_size_x, init_size_y);
	solid_body = collider;
}

sf::IntRect SolidEntity::return_rect() {
	return solid_body.get_rect();
}

std::vector<float> SolidEntity::return_collisions() {
	return solid_body.return_collisions();
}