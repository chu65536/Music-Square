#pragma once

#include <SFML/Graphics.hpp>

#include "../headers/bgmusic.h"
#include "../headers/square.h"
#include "../headers/map.h"
#include "../headers/camera.h"
#include "../headers/progressbar.h"

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