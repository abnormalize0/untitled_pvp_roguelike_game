#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObj.h"
#include "MapGenerator.h"

class GameManager {
private:
	std::vector<GameObj> game_characters;
	std::vector<GameObj> walls_and_platforms;
public:
	GameManager();
	void new_player();
	std::vector<float> pack_rectangles(std::vector<std::vector<float>> collisions);
	std::vector<float> get_solid_obj();
};

