#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "../headers/config.h"
#include "../headers/sum.h"

int main()
{   
    sf::RenderWindow window(sf::VideoMode(100, 100), "SFML works!");
    sf::Clock clock;
    window.setFramerateLimit(60);

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
        window.display();
    }

    std::cout << sum(PI, PI) << '\n';
    return 0;
}