#include "GraphicDisplay.h"

GraphicDisplay::GraphicDisplay() {}


GraphicDisplay::GraphicDisplay(float init_x, float init_y, float init_size_x, float init_size_y, const char* path) {
	rectangle_sprite.setSize(sf::Vector2f(init_size_x, init_size_y));
	rectangle_sprite.setPosition(init_x, init_y);
	texture.loadFromFile(path);
	if (init_size_x == init_size_y) {
		texture_x = init_size_x;
		texture_y = init_size_y;
	} else {
		if (init_size_x > init_size_y) {
			texture_x = init_size_y * (init_size_x / 30);
			texture_y = init_size_y;
		} else {
			texture_x = init_size_x;
			texture_y = init_size_x * (init_size_y / 30);
		}
	}
}

sf::RectangleShape GraphicDisplay::return_rectangle() {
	rectangle_sprite.setTexture(&texture);		//why
	rectangle_sprite.setTextureRect((sf::IntRect(0, 0, texture_x, texture_y)));
	texture.setRepeated(true);
	return rectangle_sprite;
}

void GraphicDisplay::move_object(float new_x, float new_y) {
	rectangle_sprite.setPosition(new_x, new_y);
}