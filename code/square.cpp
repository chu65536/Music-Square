#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/square.h"
#include "../headers/config.h"

Square::Square(float x, float y, float vel_x, float vel_y) 
{
    this->x = x;
    this->y = y;
    this->velocity_x = vel_x;
    this->velocity_y = vel_y;

    this->rect = sf::RectangleShape(sf::Vector2f(Config::SQUARE_SIZE, Config::SQUARE_SIZE));
    this->rect.setFillColor(sf::Color(50, 50, 50));
    this->rect.setOrigin(Config::SQUARE_SIZE / 2, Config::SQUARE_SIZE / 2);
    this->rect.setPosition(0.f, 0.f);
    this->rect.setOutlineThickness(Config::SQUARE_OUTLINE_THICKNESS);
    this->rect.setOutlineColor(sf::Color(Config::SQUARE_OUTLINE_COLOR));
}
void Square::update(float time){
    this->x += this->velocity_x * time;
    this->y += this->velocity_y * time;

    this->rect.setPosition(this->x, this->y);
}
void Square::draw(sf::RenderWindow& window){
    window.draw(this->rect);
}

void Square::shiftColor(){
    float r = this->rect.getFillColor().r;
    float g = this->rect.getFillColor().g;
    float b = this->rect.getFillColor().b;

    float shift_speed = 80.f;
    float min_value = 50.f;

    r -= (Config::SQUARE_COLOR.r - min_value) / shift_speed;
    g -= (Config::SQUARE_COLOR.g - min_value) / shift_speed;
    b -= (Config::SQUARE_COLOR.b - min_value) / shift_speed;

    r = std::max(min_value, r);
    g = std::max(min_value, g);
    b = std::max(min_value, b);

    this->rect.setFillColor(sf::Color(r, g, b));
}