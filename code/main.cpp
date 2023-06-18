#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "../headers/config.h"
#include "../headers/square.h"
#include "../headers/map.h"
#include "../headers/platform.h"
#include "../headers/bgmusic.h"

int main()
{    
    srand(time(0));
    // window init
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Music Square");
    window.setFramerateLimit(FPS);
    sf::Clock clock;

    // main inits
    Square square(START_X, START_Y, VELOCITY_X, VELOCITY_Y);
    Map map(square);
    BGMusic music;
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

    // main loop
    float prev_time = 0.0f, cur_time = 0.0f;
    int pt = 0;
    while (window.isOpen())
    {   
        float delta_time = clock.restart().asSeconds();        

        // event manager
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Space)
                music.play();
        }
        
        // logic
        prev_time = cur_time;
        cur_time = music.getOffset();
        float delta = cur_time - prev_time;
        while(pt < map.delays.size() && cur_time >= map.delays[pt]){
            pt++;
            square.velocity_y *= -1;
        }

        square.update(delta);
        // view
        // view.setCenter(square.x, square.y);
        // window.setView(view);

        // draw
        window.clear(sf::Color(WALLS_COLOR));

        square.draw(window);

        window.display();
    }
}