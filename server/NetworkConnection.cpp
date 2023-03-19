#include "NetworkConnection.h"

NetworkConnection::NetworkConnection(int port) { 
        listener.listen(port);
}

void NetworkConnection::new_connection() {
        sf::TcpSocket socket;
        listener.accept(players_sockets[connected_players]);
        connected_players++;
}

std::vector<float> NetworkConnection::receive_impulse() {
	std::vector<float> impulses;
	sf::Packet packet;
	socket.receive(packet);
	float impulse_x, impulse_y;
	packet >> impulse_x >> impulse_y;
	impulses.push_back(impulse_x);
	impulses.push_back(impulse_y);
	return impulses;
}

void NetworkConnection::send_objects(std::vector<float> objects) {
        for (int player = 0; player < connected_players; player++) {
                sf::Packet packet;
                packet << objects[0];
                packet << objects[player * 4 + 1];
                packet << objects[player * 4 + 2];
                packet << objects[player * 4 + 3];
                packet << objects[player * 4 + 4];
                for (int i = 1; i < objects.size(); i++) {
                        if ((i < player * 4 + 1)||(i > player * 4 + 4)) packet << objects[i];
                }
                players_sockets[player].send(packet);
        }
}