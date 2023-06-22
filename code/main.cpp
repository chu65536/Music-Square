#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

#include "../headers/config.h"
#include "../headers/square.h"
#include "../headers/map.h"
#include "../headers/platform.h"
#include "../headers/bgmusic.h"
#include "../headers/camera.h"

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
    Camera camera(START_X, START_Y, CAMERA_WIDTH, CAMERA_HEIGHT, CAMERA_BORDER);

    // main loop
    float delta_time;
    float time = 0.f;
    float current_time = 0.f;
    bool start = false;
    while (window.isOpen())
    {   
        delta_time = clock.restart().asSeconds(); 

        // event manager
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Space){
                music.play();
                start = true;
            }
        }

        // logic
        if (start){
            time += delta_time;
            current_time += delta_time;
        }
        while (time > map.delays[map.pt]){
            square.velocity_y *= -1;
            square.bounce_x = map.platforms[map.pt].x;
            square.bounce_y = map.platforms[map.pt].y;
            current_time = time - map.delays[map.pt];
            map.pt++;
        }

        square.update(current_time);
        camera.update(square);
        window.setView(camera.view);

        // draw
        window.clear(sf::Color(WALLS_COLOR));

        map.draw(window);
        square.draw(window);

        window.display();
    }
}