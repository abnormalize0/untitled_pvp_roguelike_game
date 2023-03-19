#include "GameManager.h"
#include "NetworkConnection.h"

int main() {
	NetworkConnection players(53001);
	players.new_connection();
	players.new_connection();
	GameManager game;
	players.send_objects(game.get_solid_obj());
	game.new_player();
	game.new_player();
	while (true) {
		game.frame_process( );
		std::vector<std::vector<float>> impulses;
		impulses.push_back(players.receive_impulse(0));
		impulses.push_back(players.receive_impulse(1));
		game.update_movement(impulses);
		players.send_objects(game.get_dynamic_obj());
	}
}