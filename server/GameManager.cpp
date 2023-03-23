#include "GameManager.h"

GameManager::GameManager() {
	GameObj wall1(0, 0, 30, 610);		//temp solution b4 i create map class
	GameObj wall2(770, 0, 30, 610);
	GameObj wall3(0, 570, 800, 30);
	GameObj wall4(0, 390, 400, 30);
	GameObj wall5(400, 200, 400, 30);
	GameObj wall6(0, 0, 800, 30);
	
	walls_and_platforms.push_back(wall1);
	walls_and_platforms.push_back(wall2);
	walls_and_platforms.push_back(wall3);
	walls_and_platforms.push_back(wall4);
	walls_and_platforms.push_back(wall5);
	walls_and_platforms.push_back(wall6);

	MapGenerator world;
	std::vector<std::vector<int>> map = world.create_towers(4, 1, 5);
	std::vector<GameObj> generated = world.convert_map_to_obj(map);

	walls_and_platforms.insert(walls_and_platforms.end(), generated.begin(), generated.end());
}

void GameManager::new_player() {
	GameObj player(40, 500, 40, 40);
	game_characters.push_back(player);
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

