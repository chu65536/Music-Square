#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "../headers/config.h"
#include "../headers/square.h"
#include "../headers/sound.h"
#include "../headers/map.h"
#include "../headers/platform.h"

int main()
{     
    // window init
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Music Square");
    sf::Clock clock;
    window.setFramerateLimit(FPS);

    // notemap {delay, note} (working on midi python parcer)
    std::vector<Platform> platforms;
    
    // main inits
    Square square(START_X, START_Y, DX, DY);
    Map map(START_X, START_Y, platforms);
    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 400.f));
    initSound();

    // main loop
    while (window.isOpen())
    {   
        // fps
        float current_time = clock.restart().asSeconds();
        float fps = 1.0f / (current_time);

        // event manager
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // logic
        square.Update();

        // view
        view.setCenter(square.x, square.y);
        window.setView(view);

        // draw
        window.clear(sf::Color(0, 0, 0));
        map.Draw(window);
        square.Draw(window);

        window.display();
    }
}