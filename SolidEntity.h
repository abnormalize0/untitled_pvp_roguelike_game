#pragma once

#include "SolidObj.h"
#include "GraphicDisplay.h"

class SolidEntity {
private:
	SolidObj solid_body;
	GraphicDisplay graphic_image;
public:
	SolidEntity(float init_x, float init_y, float init_size_x, float init_size_y);
	sf::RectangleShape return_graphic_image();
	sf::IntRect return_collision();
};

