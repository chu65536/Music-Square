#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/square.hpp"
#include "../headers/config.hpp"

Square::Square(float x, float y, float vel_x, float vel_y) 
{
    this->x = x;
    this->y = y;
    this->velocity_x = vel_x;
    this->velocity_y = vel_y;
    this->cycled_dx = vel_x;
    this->cycled_dy = vel_y;

    this->rect = sf::RectangleShape(sf::Vector2f(Config::SQUARE_SIZE, Config::SQUARE_SIZE));
    this->rect.setFillColor(Config::SQUARE_COLOR);
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

void Square::shiftColor(float dt){
    float r = this->rect.getFillColor().r;
    float g = this->rect.getFillColor().g;
    float b = this->rect.getFillColor().b;

    float speed = 150.f;

    r += speed * dt;
    g += speed * dt;
    b += speed * dt;

    r = std::min(r, 255.f);
    g = std::min(g, 255.f);
    b = std::min(b, 255.f);

    this->rect.setFillColor(sf::Color(r, g, b));
}