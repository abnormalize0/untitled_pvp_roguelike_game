#include "GameManager.h"

GameManager::GameManager() {
	SolidEntity wall1(0, 0, 30, 610);		//temp solution b4 i create map class
	SolidEntity wall2(770, 0, 30, 610);
	SolidEntity wall3(0, 570, 800, 30);
	SolidEntity wall4(0, 390, 400, 30);
	SolidEntity wall5(400, 200, 400, 30);
	SolidEntity wall6(0, 0, 800, 30);
	
	walls_and_platforms.push_back(wall1);
	walls_and_platforms.push_back(wall2);
	walls_and_platforms.push_back(wall3);
	walls_and_platforms.push_back(wall4);
	walls_and_platforms.push_back(wall5);
	walls_and_platforms.push_back(wall6);

}

void GameManager::new_player() {
	LivingEntity player(40, 500, 40, 40);
	game_characters.push_back(player);
}

void GameManager::frame_process() {
	std::vector<sf::IntRect> solid_objects;
	for (int i = 0; i < walls_and_platforms.size(); i++) {
		solid_objects.push_back(walls_and_platforms[i].return_rect());
	}
	for (int i = 0; i < game_characters.size(); i++) {
		game_characters[i].game_step(solid_objects);
	}
}

std::vector<float> GameManager::pack_rectangles(std::vector<std::vector<float>> collisions) {
	std::vector<float> pack;
	int size = 0;
	size = collisions.size();
	pack.push_back(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 4; j++) {
			pack.push_back(collisions[i][j]);
		}
	}
	return pack;
}

std::vector<float> GameManager::get_solid_obj() {
	std::vector<std::vector<float>> solid_objects;
	for (int i = 0; i < walls_and_platforms.size(); i++) {
		solid_objects.push_back(walls_and_platforms[i].return_collisions());
	}
	return pack_rectangles(solid_objects);
}

std::vector<float> GameManager::get_dynamic_obj(int type) {
	if (type == 0) {
		std::vector<std::vector<float>> dynamic_objects;
		for (int i = 0; i < game_characters.size(); i++) {
			dynamic_objects.push_back(game_characters[i].return_collisions());
		}
		return pack_rectangles(dynamic_objects);
	} else {
		std::vector<std::vector<float>> dynamic_objects;
		for (int i = game_characters.size() - 1; i >= 0; i--) {
			dynamic_objects.push_back(game_characters[i].return_collisions());
		}
		return pack_rectangles(dynamic_objects);
	}
}

void GameManager::update_movement(std::vector<std::vector<float>> impulses) {
	for (int i = 0; i < impulses.size(); i++) {
		game_characters[i].add_impulse(impulses[i]);
	}
}
