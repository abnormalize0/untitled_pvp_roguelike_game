#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class NetworkConnection {
private:
	sf::TcpSocket tcp_socket;
	int player_number;
public:
	NetworkConnection();
	std::vector<float> receive_objects();
	void send_impulse(std::vector<float> impulses);
	void button_process(int case_number, float x, float y);
	std::vector<int> listen_broadcast();
	void unblock();
	int get_number();
};