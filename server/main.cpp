#include "GameManager.h"
#include "NetworkConnection.h"

int main() {
	NetworkConnection player_1(53000);
	NetworkConnection player_2(53001);

	GameManager game;

	player_1.send_objects(game.get_solid_obj());
	player_2.send_objects(game.get_solid_obj());
	game.new_player();
	game.new_player();
	while (true) {
		game.frame_process();
		std::vector<std::vector<float>> impulses;
		impulses.push_back(player_1.receive_impulse());
		impulses.push_back(player_2.receive_impulse());
		game.update_movement(impulses);
		player_1.send_objects(game.get_dynamic_obj());
		player_2.send_objects(game.get_dynamic_obj());
	}
}