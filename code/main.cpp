#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "../headers/config.h"
#include "../headers/cube.h"

int main()
{   
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    sf::Clock clock;
    window.setFramerateLimit(60);

    Cube cube;
    cube.setSpeed(DX, DY);
    cube.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    sf::RectangleShape rect(sf::Vector2f(C_SIZE, C_SIZE));
    rect.setOrigin(C_HSIZE, C_HSIZE);

    while (window.isOpen())
    {
        float current_time = clock.restart().asSeconds();
        float fps = 1.0f / (current_time);
        //cout << fps << '\n';

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        cube.Update();
        rect.setPosition(cube.getX(), cube.getY());
        window.draw(rect);

        window.display();
    }
}