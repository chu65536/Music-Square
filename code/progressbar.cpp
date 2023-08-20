#include "../headers/progressbar.hpp"
#include "../headers/config.hpp"
#include <iostream>


ProgressBar::ProgressBar(){
};

ProgressBar::ProgressBar(Camera &camera, float mx_value){
    this->camera = &camera;
    this->mx_value = mx_value;

    this->x = camera.x;
    this->y = camera.y;
    if (!Config::PROGRESS_BAR_LEFT){
        float bottom_border = Config::WINDOW_HEIGHT / 100.f;
        float side_border = Config::WINDOW_WIDTH / 100.f;
        this->w = camera.w - side_border * 2;
        this->h = Config::WINDOW_HEIGHT / 50;

        this->rect = sf::RectangleShape(sf::Vector2f(this->w, this->h));
        this->rect.setOrigin(this->w / 2, -camera.h / 2 + this->h + bottom_border);  
    }
    else{
        float bottom_border = Config::WINDOW_WIDTH / 150.f;
        float side_border = Config::WINDOW_HEIGHT / 100.f;
        this->w = Config::WINDOW_WIDTH / 60;
        this->h = camera.h - side_border * 2;

        this->rect = sf::RectangleShape(sf::Vector2f(this->w, this->h));
        this->rect.setOrigin(camera.w / 2 - bottom_border, this->h / 2);
    }
    this->rect.setPosition(this->x, this->y);
    sf::Color col = Config::PROGRESS_BAR_COLOR;
    if (Config::SHOW_PROGRESS_BAR)
        col.a = 150;
    else
        col.a = 0;

    this->rect.setFillColor(col);
};

void ProgressBar::update(float val){
    this->x = this->camera->x;
    this->y = this->camera->y;

    this->rect.setPosition(this->x, this->y);
    if (!Config::PROGRESS_BAR_LEFT)
        this->rect.setSize(sf::Vector2f(this->w * val / this->mx_value, this->h));
    else
        this->rect.setSize(sf::Vector2f(this->w, this->h * val / this->mx_value));
}
