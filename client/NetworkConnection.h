#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class NetworkConnection {
private:
	sf::TcpSocket tcp_socket;
public:
	NetworkConnection();
	std::vector<float> receive_objects();
	void send_impulse(std::vector<float> impulses);
};