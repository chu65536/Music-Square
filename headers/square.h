#pragma once

#include "../headers/platform.h"

class Square{
public:
    Square(float x, float y, float vel_x, float vel_y);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    float x, y;
    float velocity_x, velocity_y;
    sf::RectangleShape rect;
};
