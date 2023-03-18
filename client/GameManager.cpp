#include "GameManager.h"
#include<iostream>

GameManager::GameManager() {
	window.create(sf::VideoMode(800, 600), "untitled pvp roguelite game");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
}

void GameManager::play() {
	init_walls_and_platforms(network_module.receive_objects());
	std::cout << "1" << std::endl;
	LivingEntity player1(40, 500, 40, 40);
	LivingEntity player2(40, 500, 40, 40);
	std::cout << "2" << std::endl;
	game_characters.push_back(player1);
	game_characters.push_back(player2);  //lol
	std::cout << "3" << std::endl;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		std::cout << "z" << std::endl;
		std::vector<float> impulses = game_characters[0].game_step();
		std::cout << "a" << std::endl;
		network_module.send_impulse(impulses);
		std::cout << "b" << std::endl;
		move_game_characters(network_module.receive_objects());

		window.clear();

		for (int i = 0; i < walls_and_platforms.size(); i++) {
			std::cout << "draw " << i << std::endl;
			window.draw(walls_and_platforms[i].return_graphic_image());
		}
		for (int i = 0; i < game_characters.size(); i++) {
			std::cout << "character drawn" << std::endl;
			window.draw(game_characters[i].return_graphic_image());
		}
		window.display();
	}
}

void GameManager::init_walls_and_platforms(std::vector<float> objects) {
	for (int i = 0; i < objects.size(); i = i + 4) {
		SolidEntity wall(objects[i + 2], objects[i + 3], objects[i], objects[i + 1]);
		walls_and_platforms.push_back(wall);
	}
}

void GameManager::move_game_characters(std::vector<float> objects) {
	int character = 0;
	for (int i = 0; i < objects.size(); i = i + 4) {
		std::cout << "new coordinates is " << objects[i + 2] << " and " << objects[i + 3] << std::endl;
		game_characters[character].change_parameters(objects[i], objects[i + 1], objects[i + 2], objects[i + 3]);
		character++;
	}
}