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
	void game_step(std::vector<sf::IntRect> solid_objects);
	void change_parameters(float new_size_x, float new_size_y, float new_pos_x, float new_pos_y);
	//void behavioral_model();
	void change_button_state(int button);
	float get_x() { return phys_body.get_x(); }
	float get_y() { return phys_body.get_y(); }
};

