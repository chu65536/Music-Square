#pragma once

#include <SFML/Graphics.hpp>

#include "../headers/bgmusic.hpp"
#include "../headers/square.hpp"
#include "../headers/map.hpp"
#include "../headers/camera.hpp"
#include "../headers/progressbar.hpp"

class Game{
    BGMusic music;   
    Square square; 
    Map map;
    Camera camera;
    ProgressBar progress_bar;
    sf::Clock clock;

    float ellapsed_time;
    bool running;
    int frame;
public:
    Game();
    void playMusic();
    void handleEvents(sf::Event);
    float getFrameTime();
    void update(float dt);
    void draw();
    void restart();

    sf::RenderWindow window;
};