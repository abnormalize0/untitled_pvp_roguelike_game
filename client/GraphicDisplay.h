#pragma once

#include <SFML/Graphics.hpp>

class GraphicDisplay {
private:
	sf::RectangleShape rectangle_sprite;
	sf::Texture texture;
	float texture_x;
	float texture_y;
	int direction = 1;
public:
	GraphicDisplay();
	GraphicDisplay(float init_x, float init_y, float init_size_x, float init_size_y, const char* path);		//do smth with this
	sf::RectangleShape return_rectangle();
	void move_object(float new_x, float new_y);
};

