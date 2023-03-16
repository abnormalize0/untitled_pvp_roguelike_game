#include "NetworkConnection.h"
#include<iostream>

NetworkConnection::NetworkConnection() {}


void NetworkConnection::init(int type) {
	role = type;
	if (type) {
		socket.bind(54000);
	} else {
		socket.bind(54001);
	}
	
}

void NetworkConnection::sending(std::vector<sf::RectangleShape> image_objects) {
	sf::IpAddress recipient = "127.0.0.1";
	unsigned short port = 54001;
	sf::Packet packet;
	int size = image_objects.size();
	packet << size;
	for (int i = 0; i < image_objects.size(); i++) {
		packet << image_objects[i].getSize().x << image_objects[i].getSize().y << image_objects[i].getPosition().x << image_objects[i].getPosition().y;
	}
	socket.send(packet, recipient, port);
}

std::vector<sf::RectangleShape> NetworkConnection::receiving() {
	std::vector<sf::RectangleShape> image_objects;
	sf::IpAddress sender = "127.0.0.1";
	unsigned short port = 54000;
	sf::Packet packet;
	socket.receive(packet, sender, port);
	int size;
	packet >> size;
	for (int i = 0; i < 7; i++) {
		float size_x, size_y, pos_x, pos_y;
		packet >> size_x;
		packet >> size_y;
		packet >> pos_x;
		packet >> pos_y;
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(size_x, size_y));
		rectangle.setPosition(sf::Vector2f(pos_x, pos_y));
		image_objects.push_back(rectangle);
	}
	return image_objects;
}

int NetworkConnection::is_server() {
	return role;
}