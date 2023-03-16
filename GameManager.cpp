#include "GameManager.h"
#include<iostream>

GameManager::GameManager(int type) {
	
	window.create(sf::VideoMode(800, 600), "untitled pvp roguelite game");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	LivingEntity player(40, 500, 40, 40);  //temp solution b4 i create map class
	SolidEntity wall1(0, 0, 30, 610);
	SolidEntity wall2(770,0, 30, 610);
	SolidEntity wall3(0, 570, 800, 30);
	SolidEntity wall4(0, 390, 400, 30);
	SolidEntity wall5(400, 200, 400, 30);
	SolidEntity wall6(0, 0, 800, 30);
	game_characters.push_back(player);
	walls_and_platforms.push_back(wall1);
	walls_and_platforms.push_back(wall2);
	walls_and_platforms.push_back(wall3);
	walls_and_platforms.push_back(wall4);
	walls_and_platforms.push_back(wall5);
	walls_and_platforms.push_back(wall6);

	network_module.init(type);
}

void GameManager::play() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (network_module.is_server()) {
			std::vector<sf::IntRect> solid_objects;
			std::vector<sf::RectangleShape> image_objects;

			for (int i = 0; i < walls_and_platforms.size(); i++) {
				window.draw(walls_and_platforms[i].return_graphic_image());
				image_objects.push_back(walls_and_platforms[i].return_graphic_image());
				solid_objects.push_back(walls_and_platforms[i].return_collision());
			}
			for (int i = 0; i < game_characters.size(); i++) {
				window.draw(game_characters[i].return_graphic_image());
				image_objects.push_back(game_characters[i].return_graphic_image());
				game_characters[i].game_step(solid_objects);
			}
			window.display();
			network_module.sending(image_objects);
		} else {
			window.clear();
			std::vector<sf::RectangleShape> image_objects;
			image_objects = network_module.receiving();
			for (int i = 0; i < image_objects.size(); i++) {
				window.draw(image_objects[i]);
			}
			window.display();
		}
	}
}