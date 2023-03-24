#include "GameManager.h"
#include <time.h>
#include<iostream>

GameManager::GameManager() {
	window.create(sf::VideoMode(800, 600), "untitled pvp roguelite game");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	view.setCenter(sf::Vector2f(800 * 0.5 + (800 / 2) , 600 * 54 + (600/2))); //make dynamic
	view.setSize(sf::Vector2f(800, 600));
	next_room = 54;
	x_position = 0.5;
	view.zoom(1);
	window.setView(view);
	init_walls_and_platforms(network_module.receive_objects());
	LivingEntity player1(800 * 0.5 + 40, 600 * 54 + 500, 40, 40);
	LivingEntity player2(800 * 0.5 + 40, 600 * 54 + 500, 40, 40);
	game_characters.push_back(player1);
	game_characters.push_back(player2);
	transition_left = 0;
}

void GameManager::play() {
	int time = std::time(0);
	int frames = 0;
	int button_states[3] = { 0 };
	network_module.unblock();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::A) {
					if (!button_states[0]) {
						button_states[0] = 1;
						network_module.button_process(1, game_characters[network_module.get_number()].get_x(), game_characters[network_module.get_number()].get_y());
						game_characters[network_module.get_number()].change_button_state(1);
					}
				}
				if (event.key.code == sf::Keyboard::D) {
					if (!button_states[1]) {
						button_states[1] = 1;
						network_module.button_process(2, game_characters[network_module.get_number()].get_x(), game_characters[network_module.get_number()].get_y());
						game_characters[network_module.get_number()].change_button_state(2);
					}
				}
				if (event.key.code == sf::Keyboard::Space) {
					if (!button_states[2]) {
						button_states[2] = 1;
						network_module.button_process(3, game_characters[network_module.get_number()].get_x(), game_characters[network_module.get_number()].get_y());
						game_characters[network_module.get_number()].change_button_state(3);
					}
				}
			} 
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::A) {
					if (button_states[0]) {
						button_states[0] = 0;
						network_module.button_process(-1, game_characters[network_module.get_number()].get_x(), game_characters[network_module.get_number()].get_y());
						game_characters[network_module.get_number()].change_button_state(-1);
					}
				}
				if (event.key.code == sf::Keyboard::D) {
					if (button_states[1]) {
						button_states[1] = 0;
						network_module.button_process(-2, game_characters[network_module.get_number()].get_x(), game_characters[network_module.get_number()].get_y());
						game_characters[network_module.get_number()].change_button_state(-2);
					}
				}
				if (event.key.code == sf::Keyboard::Space) {
					if (button_states[2]) {
						button_states[2] = 0;
						network_module.button_process(-3, game_characters[network_module.get_number()].get_x(), game_characters[network_module.get_number()].get_y());
						game_characters[network_module.get_number()].change_button_state(-3);
					}
				}
			}
		}

		window.clear();

		std::vector<sf::IntRect> solid_objects;

		for (int i = 0; i < walls_and_platforms.size(); i++) {
			window.draw(walls_and_platforms[i].return_graphic_image());
			solid_objects.push_back(walls_and_platforms[i].return_collision());
		}
		for (int i = 0; i < game_characters.size(); i++) {
			window.draw(game_characters[i].return_graphic_image());
			game_characters[i].game_step(solid_objects);
		}

		if (game_characters[network_module.get_number()].get_y() < 600 * next_room + 30) {
			std::cout << 600 * next_room + 30 << " " << game_characters[network_module.get_number()].get_y() << " " << "exceed" << std::endl;
			next_room--;
			if (game_characters[network_module.get_number()].get_x() > x_position * 800 + 400) {
				x_position = x_position + 0.5;
				//view.move(400, -600);
				transition_left = 20;
				game_characters[network_module.get_number()].change_parameters(40, 40, game_characters[network_module.get_number()].get_x(), 600 * next_room + 500);
				std::cout << "right" << std::endl;
			} else {
				x_position = x_position - 0.5;
				//view.move(-400, -600);
				transition_left = -20;
				game_characters[network_module.get_number()].change_parameters(40, 40, game_characters[network_module.get_number()].get_x(), 600 * next_room + 500);
				std::cout << "left" << std::endl;
			}
			//view.setCenter(sf::Vector2f(800 * x_position + (800 / 2), 600 * next_room + (600 / 2)));
		}
		camera_transition();
		window.display();

		std::vector<int> button_update = network_module.listen_broadcast();
		if (button_update[0] != 0) {
			game_characters[button_update[1]].change_button_state(button_update[0]);
			std::cout << button_update[2] << " + " << button_update[3] << std::endl;
			game_characters[button_update[1]].change_parameters(40, 40, button_update[2], button_update[3]);
		}
	}
}

void GameManager::init_walls_and_platforms(std::vector<float> objects) {
	for (int i = 0; i < objects.size(); i = i + 4) {
		SolidEntity wall(objects[i + 2], objects[i + 3], objects[i], objects[i + 1]);
		walls_and_platforms.push_back(wall);
	}
}

void GameManager::camera_transition() {
	if (transition_left != 0) {
		if (transition_left > 0) {
			view.move(10*2, -15*2);
			transition_left--;
		} else {
			view.move(-10*2, -15*2);
			transition_left++;
		}
		window.setView(view);
	}
}