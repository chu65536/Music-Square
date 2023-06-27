#include "../headers/config.h"
#include "../headers/camera.h"
#include <cmath>

Camera::Camera(float x, float y, float w, float h, float border){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->border = border;

    this->view = sf::View(sf::Vector2f(x, y), sf::Vector2f(w, h));

    this->font.loadFromFile("src/fonts/trebuc.ttf");
    this->fps.setFont(this->font);
    this->fps.setCharacterSize(100);
    this->fps.setScale(0.2f, 0.2f);
    this->fps.setFillColor(sf::Color::Yellow);
    this->fps_counter = 0;
    this->fps_timer = 0.f;
    this->fps_str = "0";
}

void Camera::update(Square &square){
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

void Camera::drawFPS(sf::RenderWindow& window, float dt){
    this->fps_timer += dt;
    this->fps_counter++;
    if (this->fps_timer > 1.f){
        this->fps_str = std::to_string(int(fps_counter / fps_timer));
        this->fps_timer = 0.f;
        this->fps_counter = 0;
    }

    this->fps.setString(this->fps_str);
    this->fps.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
    window.draw(this->fps);
}