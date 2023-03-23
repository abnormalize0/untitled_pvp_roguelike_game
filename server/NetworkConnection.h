#pragma once

#include <SFML/Network.hpp>

class NetworkConnection {
private:
    sf::TcpListener listener;
    sf::TcpSocket players_sockets[2];
    int connected_players = 0;
public:
    NetworkConnection(int port);
    void send_objects(std::vector<float> objects);
    void new_connection();
    void button_process(int player);
};