#pragma once

#include <SFML/Graphics.hpp>
#include "../headers/square.hpp"

class Camera{
public:
    Camera(float x = 0.f, float y = 0.f, float w = 1920.f, float h = 1080.f);
    void update(Square &squarem, float dt);

    float x;
    float y;
    float w;
    float h;
    sf::View view;
};