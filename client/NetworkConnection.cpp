#include "NetworkConnection.h"
#include<iostream>

NetworkConnection::NetworkConnection() {
	tcp_socket.connect("ovz3.abnormalize.m6x5m.vps.myjino.ru", 49275);
	sf::Packet packet;
	int number = 0;
	tcp_socket.receive(packet);
	packet >> number;
	player_number = number;
}

std::vector<float> NetworkConnection::receive_objects() {
	sf::Packet packet;
	tcp_socket.receive(packet);
	float size = 0;
	packet >> size;
	std::vector<float> objects;
	for (int i = 0; i < int(size) * 4; i++) {
		float parameter = 0;
		packet >> parameter;
		objects.push_back(parameter);
	}
	return objects;
}

void NetworkConnection::button_process(int case_number, float x, float y) {
	sf::Packet packet;
	packet << case_number << x << y;
	tcp_socket.send(packet);
}

std::vector<int> NetworkConnection::listen_broadcast() {
	std::vector<int> hearsay;
	int button = 0;
	int player = 0;
	float x = 0;
	float y = 0;
	sf::Packet packet;
	tcp_socket.receive(packet);
	packet >> x >> y >> button >> player;
	hearsay.push_back(button);
	hearsay.push_back(player);
	hearsay.push_back(x);
	hearsay.push_back(y);
	return hearsay;
}

void NetworkConnection::unblock() {
	tcp_socket.setBlocking(false);
}

int NetworkConnection::get_number() {
	return player_number;
}