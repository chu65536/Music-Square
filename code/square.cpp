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
    this->rect.setFillColor(sf::Color(Config::SQUARE_COLOR));
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