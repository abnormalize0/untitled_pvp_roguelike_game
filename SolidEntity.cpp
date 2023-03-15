#include "SolidEntity.h"

SolidEntity::SolidEntity(float init_x, float init_y, float init_size_x, float init_size_y) {
	SolidObj collider(init_x, init_y, init_size_x, init_size_y);
	solid_body = collider;
	GraphicDisplay sprite(init_x, init_y, init_size_x, init_size_y, "images/brick.png");
	graphic_image = sprite;
}

sf::RectangleShape SolidEntity::return_graphic_image() {
	return graphic_image.return_rectangle();
}

sf::IntRect SolidEntity::return_collision() {
	return solid_body.get_collision();
}