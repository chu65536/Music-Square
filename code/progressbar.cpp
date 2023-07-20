#include "../headers/progressbar.hpp"
#include "../headers/config.hpp"
#include <iostream>


ProgressBar::ProgressBar(){
};

ProgressBar::ProgressBar(Camera &camera, float mx_value){
    this->camera = &camera;
    this->mx_value = mx_value;

    float bottom_border = Config::WINDOW_HEIGHT / 100.f;
    float side_border = Config::WINDOW_WIDTH / 100.f;
    this->x = camera.x;
    this->y = camera.y;
    this->w = camera.w - side_border * 2;
    this->h = Config::WINDOW_WIDTH / 60;

    this->rect = sf::RectangleShape(sf::Vector2f(this->w, this->h));
    this->rect.setOrigin(this->w / 2, -camera.h / 2 + this->h + bottom_border);
    this->rect.setPosition(this->x, this->y);
    this->rect.setFillColor(sf::Color(0, 0, 0, 150));  
};

void ProgressBar::update(float val){
    this->x = this->camera->x;
    this->y = this->camera->y;

    this->rect.setPosition(this->x, this->y);
    this->rect.setSize(sf::Vector2f(this->w * val / this->mx_value, this->h));
}
