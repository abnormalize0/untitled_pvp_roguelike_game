#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "LivingEntity.h"
#include "SolidEntity.h"

class GameManager {
private:
	sf::RenderWindow window;
	std::vector<LivingEntity> game_characters;
	std::vector<SolidEntity> walls_and_platforms;
public:
	GameManager();
	void play();
};