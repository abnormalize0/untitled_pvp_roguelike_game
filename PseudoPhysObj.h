#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
class PseudoPhysObj {
private:
    float x;
    float y;
    float size_x;
    float size_y;
    float next_x;
    float next_y;

    float air_friction = 1.1;
    float ground_friction = 1.2;

    float impulse_x = 0.0;
    float impulse_y = 0.0;

    int state;
public:
    PseudoPhysObj(float init_x, float init_y, float init_size_x, float init_size_y);
    void controller();
    void physics_process(std::vector<sf::IntRect> solid_objects);
    void resolve_collisions(std::vector<sf::IntRect> solid_objects);
    void resolve_collisions_v2(std::vector<sf::IntRect> solid_objects);
    void resolve_collisions_v3(std::vector<sf::IntRect> solid_objects);
    void precise_position_x(sf::IntRect collision);
    void precise_position_y(sf::IntRect collision);
    float get_x() { return x; }
    float get_y() { return y; }

};
