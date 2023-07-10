#pragma once

#include <SFML/Graphics.hpp>

#include "../headers/bgmusic.h"
#include "../headers/square.h"
#include "../headers/map.h"
#include "../headers/camera.h"

class Game{
    BGMusic music;   
    Square square; 
    Map map;
    Camera camera;
    sf::Clock clock;

    bool running;
    int frame;
public:
    Game();
    void playMusic();
    void handleEvents(sf::Event);
    float getEllapsedTime();
    void update(float dt);
    void draw();

    sf::RenderWindow window;
};