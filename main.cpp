#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <time.h>
#include <math.h>

#include "PseudoPhysObj.h"
#include "SolidObj.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pseudo phys 0 FPS");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    PseudoPhysObj player(40, 500, 40, 40);
    SolidObj wall1(0, -10, 10, 610);
    SolidObj wall2(790, -10, 10, 610);
    SolidObj wall3(0, 590, 800, 10);
    SolidObj wall4(0, 390, 400, 30);
    SolidObj wall5(400, 200, 400, 30);
    SolidObj wall6(0, -20, 800, 30);

    sf::CircleShape shape(20.f);
    shape.setPosition(40, 500);
    shape.setFillColor(sf::Color::Green);

    sf::RectangleShape rectangle1(sf::Vector2f(10, 600));
    rectangle1.setPosition(0, 0);
    sf::RectangleShape rectangle2(sf::Vector2f(10, 600));
    rectangle2.setPosition(790, 0);
    sf::RectangleShape rectangle3(sf::Vector2f(800, 10));
    rectangle3.setPosition(0, 590);
    sf::RectangleShape rectangle4(sf::Vector2f(400, 30));
    rectangle4.setPosition(0, 390);
    sf::RectangleShape rectangle5(sf::Vector2f(400, 30));
    rectangle5.setPosition(400, 200);
    sf::RectangleShape rectangle6(sf::Vector2f(800, 30));
    rectangle6.setPosition(0, -20);

    std::vector<sf::RectangleShape> display_objects = { rectangle1, rectangle2, rectangle3, rectangle4, rectangle5, rectangle6 };

    std::vector<sf::IntRect> solid_objects = { wall1.get_collision(), wall2.get_collision(), wall3.get_collision(),
                                                wall4.get_collision(), wall5.get_collision(),wall6.get_collision() };

    time_t seconds;
    seconds = time(NULL);
    int fps = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        for (int i = 0; i < display_objects.size(); i++) {
            window.draw(display_objects[i]);
        }
        window.display();
        player.controller();
        player.physics_process(solid_objects);
        shape.setPosition(player.get_x(), player.get_y());


        if (seconds != time(NULL)) {
            std::string title = "Pseudo phys test " + std::to_string(fps) + " FPS";
            window.setTitle(title);
            seconds = time(NULL);
            fps = 0;
        }
        else {
            fps++;
        }
    }

    return 0;
}
