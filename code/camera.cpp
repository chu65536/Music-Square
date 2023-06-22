#include "../headers/config.h"
#include "../headers/camera.h"

Camera::Camera(float x, float y, float w, float h, float border){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->border = border;

    this->view = sf::View(sf::Vector2f(x, y), sf::Vector2f(w, h));
}

void Camera::update(Square& square){
    if (square.x - this->x >this->border)
        this->x += (square.x - this->x) - this->border;
    if (square.x - this->x < -this->border)
        this->x -= -this->border - (square.x - this->x);

    if (square.y - this->y > this->border)
        this->y += (square.y - this->y) - this->border;
    if (square.y - this->y < -this->border)
        this->y -= -this->border - (square.y - this->y);

    this->view.setCenter(this->x, this->y);
}