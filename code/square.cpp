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
    this->bounce_x = START_X;
    this->bounce_y = START_Y;

    this->rect = sf::RectangleShape(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    this->rect.setFillColor(sf::Color(SQUARE_COLOR));
    this->rect.setOrigin(SQUARE_SIZE / 2, SQUARE_SIZE / 2);
    this->rect.setOutlineThickness(OUTLINE_THICKNESS);
    this->rect.setOutlineColor(sf::Color(OUTLINE_COLOR));
}
void Square::update(float time){
    this->x = this->bounce_x + this->velocity_x * time;
    this->y = this->bounce_y + this->velocity_y * time;

    this->rect.setPosition(this->x, this->y);
}
void Square::draw(sf::RenderWindow& window){
    window.draw(this->rect);
}