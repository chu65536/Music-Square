#pragma once

#include <SFML/Graphics.hpp>

#include "../headers/camera.hpp"

class ProgressBar{
    float x, y;
    float w, h;
    float mx_value;
    Camera *camera;
public:
    ProgressBar();
    ProgressBar(Camera &camera, float mx_value);
    void update(float val);

    sf::RectangleShape rect;
};