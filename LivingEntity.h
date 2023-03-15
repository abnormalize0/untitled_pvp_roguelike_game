#pragma once

#include <vector>
#include "PseudoPhysObj.h"
#include "GraphicDisplay.h"
#include "WeaponCharacteristics.h"

class LivingEntity {
private:
	PseudoPhysObj phys_body;
	GraphicDisplay graphic_image;
	//WeaponCharacteristics current_weapon;
public:
	LivingEntity(float init_x, float init_y, float init_size_x, float init_size_y);
	sf::RectangleShape return_graphic_image();
	void game_step(std::vector<sf::IntRect>);
	//void behavioral_model();
};

