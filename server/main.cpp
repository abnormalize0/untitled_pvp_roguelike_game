#include "GameManager.h"
#include "NetworkConnection.h"
#include <iostream>

int main() {
    NetworkConnection players(53001);
    players.new_connection();
    std::cout << "1st connected" << std::endl;
    players.new_connection();
    std::cout << "2nd connected" << std::endl;
    GameManager game;
    players.send_objects(game.get_solid_obj());
    game.new_player();
    game.new_player();
    while (true) {
        players.button_process(0);
        players.button_process(1);
    }
}