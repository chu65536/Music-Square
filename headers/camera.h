#pragma once

#include <SFML/Graphics.hpp>
#include "../headers/square.h"

class Camera{
    float x;
    float y;
    float w;
    float h;

    sf::Font font;
    sf::Text fps;
    float fps_timer;
    int fps_counter;
    std::string fps_str;

public:
    Camera(float x = 0.f, float y = 0.f, float w = 1920.f, float h = 1080.f);
    void update(Square &square);
    void drawFPS(sf::RenderWindow& window, float dt);

    sf::View view;
};