#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "LivingEntity.h"
#include "SolidEntity.h"
#include "NetworkConnection.h"

class GameManager {
private:
	sf::RenderWindow window;
	NetworkConnection network_module;
	std::vector<LivingEntity> game_characters;
	std::vector<SolidEntity> walls_and_platforms;

	void init_walls_and_platforms(std::vector<float>);
	void move_game_characters(std::vector<float>);
public:
	GameManager();
	void play();
};