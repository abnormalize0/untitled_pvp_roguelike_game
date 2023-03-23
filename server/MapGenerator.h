#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameObj.h"

class MapGenerator {
private:

public:
	MapGenerator();
	std::vector<std::vector<int>> create_towers(int players, int chunk_size, int start_gap);
	std::vector<int> build_floor(std::vector<int> previous_floor, int next_floor_size);
	std::vector<int> adjust(std::vector<int> floor, int floor_size, int reference_size);
	std::vector<GameObj> convert_map_to_obj(std::vector<std::vector<int>> map);
};

