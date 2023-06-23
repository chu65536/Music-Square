#pragma once

#include <SFML/Graphics.hpp>
#include "../headers/square.h"

class Camera{
    float x;
    float y;
    float w;
    float h;
    float border;

    sf::Font font;
    sf::Text fps;
    float fps_timer;
    int fps_counter;
    std::string fps_str;

public:
    Camera(float x, float y, float w, float h, float border);
    void update(Square& square);
    void drawFPS(sf::RenderWindow& window, float dt);

    sf::View view;
};