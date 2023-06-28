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
    Config::readConfig();

    // maint inits
    BGMusic music;
    Square square(0.f, 0.f, Config::VELOCITY_X, Config::VELOCITY_Y);
    Map map(square); map.pt++;
    float camera_w = Config::WINDOW_WIDTH * Config::CAMERA_ZOOM;
    float camera_h = Config::WINDOW_HEIGHT * Config::CAMERA_ZOOM;
    Camera camera(0.f, 0.f, camera_w, camera_h);
    sf::Clock clock;

    // window init
    sf::RenderWindow window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Music Square");
    window.setVerticalSyncEnabled(true);

    // main loop inits
    float accumulator = Config::OFFSET;
    float dt = 1.f / Config::FPS;
    float time = 0.f;

    bool start = false;
    int frames = 0;

    // main loop
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
        window.clear(sf::Color(Config::WALLS_COLOR));
        
        map.drawPlatforms(window);
        map.drawBG(window);
        square.draw(window);

        camera.drawFPS(window, frame_t);

        window.display();
    }
}