#include "../headers/config.hpp"
#include "../headers/camera.hpp"
#include <cmath>

float lerp(float a, float b, float f)
{
    return a * (1.0 - f) + (b * f);
}

Camera::Camera(float x, float y, float w, float h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->view = sf::View(sf::Vector2f(x, y), sf::Vector2f(w, h));
}

void Camera::update(Square &square, float dt){
    float smooth = Config::CAMERA_SPEED;

    float desired_x = square.x;
    float desired_y = square.y;

    float new_x = lerp(this->x, desired_x, smooth * dt);
    float new_y = lerp(this->y, desired_y, smooth * dt);

    this->x = new_x;
    this->y = new_y;

    this->view.setCenter(this->x, this->y);
}