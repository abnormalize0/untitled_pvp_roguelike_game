#pragma once

#include <SFML/Network.hpp>
#pragma once

#include <SFML/Graphics.hpp>

class NetworkConnection {
private:
	int role;
	sf::UdpSocket socket;
public:
	NetworkConnection();
	void init(int type);
	void sending(std::vector<sf::RectangleShape> image_objects);
	std::vector<sf::RectangleShape> receiving();
	int is_server();
};