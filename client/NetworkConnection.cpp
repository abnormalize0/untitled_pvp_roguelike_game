#include "NetworkConnection.h"
#include<iostream>

NetworkConnection::NetworkConnection() {
	tcp_socket.connect("", 49264);
	std::cout << "connected i guess" << std::endl;
}

std::vector<float> NetworkConnection::receive_objects() {
	std::cout << "1" << std::endl;
	sf::Packet packet;
	tcp_socket.receive(packet);
	std::cout << "2" << std::endl;
	float size = 0;
	packet >> size;
	std::cout << "size is " << size << std::endl;
	std::cout << "3" << std::endl;
	std::vector<float> objects;
	for (int i = 0; i < int(size) * 4; i++) {
		std::cout << "4" << std::endl;
		float parameter = 0;
		packet >> parameter;
		std::cout << parameter << std::endl;
		objects.push_back(parameter);
	}
	return objects;
}

void NetworkConnection::send_impulse(std::vector<float> impulses) {
	sf::Packet packet;
	packet << impulses[0] << impulses[1];
	tcp_socket.send(packet);
}