#include "NetworkConnection.h"

NetworkConnection::NetworkConnection(int port) {
	sf::TcpListener listener;
	listener.listen(port);
	listener.accept(socket);
}

std::vector<float> NetworkConnection::receive_impulse() {
	std::vector<float> impulses;
	sf::Packet packet;
	socket.receive(packet);
	float impulse_x, impulse_y;
	packet >> impulse_x >> impulse_y; //?
	impulses.push_back(impulse_x);
	impulses.push_back(impulse_y);
	return impulses;
}

void NetworkConnection::send_objects(std::vector<float> objects) {
	sf::Packet packet;
	for (int i = 0; i < objects.size(); i++) {
		packet << objects[i];
	}
	socket.send(packet);
}