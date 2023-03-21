#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "LivingEntity.h"
#include "SolidEntity.h"

class GameManager {
private:
	std::vector<LivingEntity> game_characters;
	std::vector<SolidEntity> walls_and_platforms;
public:
	GameManager();
	void new_player();
	void frame_process();
	std::vector<float> pack_rectangles(std::vector<std::vector<float>> collisions);
	std::vector<float> get_solid_obj();
	std::vector<float> get_dynamic_obj(int type);
	void update_movement(std::vector<std::vector<float>> impulses);
};

