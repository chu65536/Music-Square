#pragma once

#include <SFML/Graphics.hpp>
#include "../headers/square.h"

class Camera{
    float x;
    float y;
    float w;
    float h;
    float border;

public:
    Camera(float x, float y, float w, float h, float border);
    void update(Square& square);

    sf::View view;
};