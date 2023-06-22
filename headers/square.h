#pragma once

#include "../headers/platform.h"

class Square{
public:
    Square(float x, float y, float vel_x, float vel_y);
    void update(float time);
    void draw(sf::RenderWindow& window);

    float x, y;
    float velocity_x, velocity_y;
    float bounce_x, bounce_y;
    sf::RectangleShape rect;
};
