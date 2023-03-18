#pragma once

#include <SFML/Network.hpp>

class NetworkConnection { 
private:
	sf::TcpSocket socket;
public:
	NetworkConnection(int port);
	std::vector<float> receive_impulse();
	void send_objects(std::vector<float> objects);
};

