#pragma once

#include <SFML/Network.hpp>

class NetworkConnection { 
private:
	sf::TcpListener listener;
	sf::TcpSocket players_sockets[2];
	int connected_players = 0;
public:
	NetworkConnection(int port);
	std::vector<float> receive_impulse(int player);
	void send_objects(std::vector<float> objects);
	void new_connection();
};