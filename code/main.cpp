#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "../headers/config.h"
#include "../headers/square.h"
#include "../headers/sound.h"
#include "../headers/map.h"

int main()
{     
    // window init
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    sf::Clock clock;
    window.setFramerateLimit(FPS);

    // notemap {delay, note} (working on midi python parcer)
    std::vector<std::pair<int, int>> notes = {{1000, 1}, {1000, 3}, {1000, 5}, {1000, 7}};
    
    // main inits
    Square square;
    square.Init();

    Map map;
    map.Build(square, notes);
    initSound();

    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 400.f));
    // main loop
    while (window.isOpen())
    {   
        // fps
        float current_time = clock.restart().asSeconds();
        float fps = 1.0f / (current_time);
        // std::cout << fps << '\n';


        // event manager
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // logic
        if (square.getStep() == map.platforms.size())
            square.setStep(0);
        square.Update(map.getPlatform(square.getStep()));
        view.setCenter(square.getX(), square.getY());
        window.setView(view);

        // draw
        window.clear(sf::Color(0, 0, 0));

        map.Draw(window);
        square.Draw(window);

        window.display();
    }
}