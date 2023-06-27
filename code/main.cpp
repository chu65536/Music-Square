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
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;

    // main inits
    Square square(START_X, START_Y, VELOCITY_X, VELOCITY_Y);
    Map map(square); map.pt++;
    BGMusic music;
    Camera camera(START_X, START_Y, CAMERA_WIDTH, CAMERA_HEIGHT, CAMERA_BORDER);


    float accumulator = OFFSET;
    float dt = 1.f / FPS;
    float time = 0.f;

    bool start = false;
    int frames = 0;
    while (window.isOpen())
    {      
        // event manager
        sf::Event event;
        while (window.pollEvent(event))
        {   
            // window close
            if (event.type == sf::Event::Closed)
                window.close();

            // keyboard
            if (event.type == sf::Event::KeyPressed){
                sf::Keyboard::Key key = event.key.code;
                switch(key){
                    // play/pause
                    case sf::Keyboard::Space: 
                        music.play();
                        start = !start;
                        break;
                    // exit
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                }
            }
        }
        
        // logic
        float frame_t = clock.restart().asSeconds();

        if (start){
            accumulator += frame_t;
            time += frame_t;
        }

        while(accumulator >= dt){
            square.update(dt);
            frames++;
            bool collided = false;
            while (frames == map.platforms[map.pt].frame){
                map.pt++;
                square.velocity_y *= -1;
                collided = true;
            }
            accumulator -= dt;
            if (collided)
                break;
        }

        // camera
        camera.update(square);
        window.setView(camera.view);

        // draw
        window.clear(sf::Color(WALLS_COLOR));
        
        map.drawPlatforms(window);
        map.drawBG(window);
        square.draw(window);

        camera.drawFPS(window, frame_t);

        window.display();
    }
}