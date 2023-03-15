#include "LivingEntity.h"

LivingEntity::LivingEntity(float init_x, float init_y, float init_size_x, float init_size_y) {
	PseudoPhysObj collider(init_x, init_y, init_size_x, init_size_y);
	phys_body = collider;
	GraphicDisplay sprite(init_x, init_y, init_size_x, init_size_y, "images/hero.png");
	graphic_image = sprite;
}

sf::RectangleShape LivingEntity::return_graphic_image() {
	return graphic_image.return_rectangle();
}

void LivingEntity::game_step(std::vector<sf::IntRect> solid_objects) {
	phys_body.controller(); //only for player, replace to behavioral_model in next version
	phys_body.physics_process(solid_objects);
	graphic_image.move_object(phys_body.get_x(), phys_body.get_y());
}