#include "MapGenerator.h"

void diplay_map(std::vector<std::vector<int>> map) {
	for (int i = map.size() - 1; i >= 0; i--) {
		if (map[i].size() % 2 == 1) {
			std::cout << " ";
		}
		for (int j = 0; j < map[i].size(); j++) {
			std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void display_floor(std::vector<int > floor) {
	for (int i = 0; i < floor.size(); i++) {
		std::cout << floor[i] << " ";
	}
	std::cout << std::endl;
}

int change(int var) {
	if (var) {
		return 0;
	} else {
		return 1;
	}
}

MapGenerator::MapGenerator() { }

std::vector<std::vector<int>> MapGenerator::create_towers(int players, int chunk_repeats, int start_gap) {
	std::srand(std::time(nullptr));
	//int initial_rooms = players * 2 - 1;
	int initial_rooms = players + (start_gap * (players - 1));
	int number_of_chunks = initial_rooms - 1;
	std::vector<std::vector<int>> map;
	int lesser = initial_rooms;
	int higher = lesser + 1;
	int order = 1;

	std::vector<int> last_floor;
	for (int i = 0; i < players * 2 - 1; i++) {
		if (!order) {
			for (int j = 0; j < start_gap; j++) {
				last_floor.push_back(order);
			}
		} else {
			last_floor.push_back(order);
		}
		order = change(order);
	}
	map.push_back(last_floor);


	for (int i = 0; i < number_of_chunks; i++) {
		for (int j = 0; j < chunk_repeats; j++) {
			last_floor = build_floor(last_floor, higher);
			map.push_back(adjust(last_floor, higher, initial_rooms + 1));
			last_floor = build_floor(last_floor, lesser);
			map.push_back(adjust(last_floor, lesser, initial_rooms + 1));
		}
		lesser--;
		higher--;
		last_floor = build_floor(last_floor, lesser);
		map.push_back(adjust(last_floor, lesser, initial_rooms + 1));
	}
	diplay_map(map);
	return map;
}

std::vector<int> MapGenerator::build_floor(std::vector<int> previous_floor, int next_floor_size) {
	std::vector<int> next_floor;
	int begin = 0;
	int end = previous_floor.size();
	if (previous_floor.size() > next_floor_size) {
		if (previous_floor[0] == 1) {
			next_floor.push_back(1);
		} else {
			next_floor.push_back(0);
		}
		begin++;
		end--;
	} else {
		if (previous_floor[0] == 1) {
			next_floor.push_back(1);
		} else {
			next_floor.push_back(0);
		}
	}
	for (int i = begin; i < end; i++) {
		if (previous_floor[i] == 1) {
			if (next_floor.back() == 1) {
				if (std::rand() % 4) {
					next_floor.push_back(1);
				} else {
					next_floor.push_back(0);
				}
			} else {
				next_floor.push_back(1);
			}
		} else {
			if ((i + 1 < end) && (previous_floor[i + 1] == 1)) {
				if (std::rand() % 4) {
					next_floor.push_back(1);
				} else {
					next_floor.push_back(0);
				}
			} else {
				next_floor.push_back(0);
			}
		}
	}
	if (previous_floor.size() > next_floor_size) {
		if (previous_floor[previous_floor.size() - 1] == 1) next_floor[next_floor.size() - 1] = 1;
	}
	return next_floor;
}

std::vector<int> MapGenerator::adjust(std::vector<int> floor, int floor_size, int reference_size) {
	std::vector<int> adjusted = floor;
	//std::cout << reference_size << " " << floor_size << " " << ((reference_size - floor_size) / 2) << std::endl;
	for (int i = 0; i < ((reference_size - floor_size) / 2); i++) {
		adjusted.insert(adjusted.begin(), 0);
		adjusted.push_back(0);
	}
	return adjusted;
}

std::vector<GameObj> MapGenerator::convert_map_to_obj(std::vector<std::vector<int>> map) {
	std::vector<GameObj> map_objects;
	int height = 600;
	int width = 800;
	int current_width = 0;
	int current_hegiht = 0;
	for (int i = map.size() - 1; i >= 0; i--) {
		if (map[i].size() % 2 == 1) {
			current_width = width / 2;
		} else {
			current_width = 0;
		}
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j]) {
				GameObj room_wall1(current_width, current_hegiht, 30, 600);		//outer walls
				GameObj room_wall2(current_width + 770, current_hegiht, 30, 600);
				GameObj room_wall3(current_width, current_hegiht + 570, 800, 30);
				//GameObj room_wall4(current_width, current_hegiht, 800, 30);
				//GameObj room_wall1(current_width, current_hegiht, 30, 610);
				//GameObj room_wall1(current_width, current_hegiht, 30, 610);
				GameObj room_wall4(current_width + 400, current_hegiht + 200, 400, 30);		//interier
				GameObj room_wall5(current_width, current_hegiht + 390, 400, 30);
				map_objects.push_back(room_wall1);
				map_objects.push_back(room_wall2);
				map_objects.push_back(room_wall3);
				map_objects.push_back(room_wall4);
				map_objects.push_back(room_wall5);

				GameObj room_separator(current_width + 370, current_hegiht, 60, 30);
				map_objects.push_back(room_separator);

				if (i == map.size() - 1) {		//specify ceiling
					GameObj room_ceil(current_width, current_hegiht, 800, 30);
					map_objects.push_back(room_ceil);
				} else {
					int total_walls = 0;
					if (map[i].size() > map[i + 1].size()) {
						if (j == 0) {
							GameObj room_ceil(current_width, current_hegiht, 400, 30);
							map_objects.push_back(room_ceil);
							total_walls++;
						} else if (j == map[i].size() - 1) {
							GameObj room_ceil(current_width + 400, current_hegiht, 400, 30);
							map_objects.push_back(room_ceil);
							total_walls++;
						} else {
							if (!map[i + 1][j - 1]) {
								GameObj room_ceil(current_width, current_hegiht, 400, 30);
								map_objects.push_back(room_ceil);
								total_walls++;
							}
							if (!map[i + 1][j]) {
								GameObj room_ceil(current_width + 400, current_hegiht, 400, 30);
								map_objects.push_back(room_ceil);
								total_walls++;
							}
						}
					} else {
						if (!map[i + 1][j]) {
							GameObj room_ceil(current_width, current_hegiht, 400, 30);
							map_objects.push_back(room_ceil);
							total_walls++;
						}
						if (!map[i + 1][j + 1]) {
							GameObj room_ceil(current_width + 400, current_hegiht, 400, 30);
							map_objects.push_back(room_ceil);
							total_walls++;
						}
					}
				}
			} 
			current_width = current_width + width;
		}
		current_hegiht = current_hegiht + height;
	}
	return map_objects;
}