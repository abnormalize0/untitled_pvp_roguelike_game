#include "NetworkConnection.h"

NetworkConnection::NetworkConnection(int port) {
    listener.listen(port);
}

void NetworkConnection::new_connection() {
    listener.accept(players_sockets[connected_players]);
    sf::Packet packet;
    packet << connected_players;
    players_sockets[connected_players].send(packet);
    players_sockets[connected_players].setBlocking(false);
    connected_players++;
}

std::vector<float> NetworkConnection::receive_impulse(int player) {
    std::vector<float> impulses;
    sf::Packet packet;
    players_sockets[player].receive(packet);
    float impulse_x, impulse_y;
    packet >> impulse_x >> impulse_y; //?
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
        //packet << objects[player];
        for (int i = 1; i < objects.size(); i++) {
            if ((i < player * 4 + 1) || (i > player * 4 + 4)) packet << objects[i];
        }
        players_sockets[player].send(packet);
    }
}

void NetworkConnection::button_process(int player) {
    int button_case = 0;
    float x = 0;
    float y = 0;
    sf::Packet packet;
    players_sockets[player].receive(packet);
    packet >> button_case;
    packet >> x;
    packet >> y;
    if (button_case != 0) {
        sf::Packet packet2;
        packet2 << x << y << button_case << player;
        for (int i = 0; i < connected_players; i++) {
            if (i != player) players_sockets[i].send(packet2);
        }
    }
}

void NetworkConnection::broadcast(int source, int button) {
    sf::Packet packet;
    packet << button << source;
    for (int i = 0; i < connected_players; i++) {
        if (i != source) players_sockets[i].send(packet);
    }
}