#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/square.h"
#include "../headers/config.h"
#include "../headers/sound.h"

Square::Square(int x, int y, int dx, int dy) 
{
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;

    this->rect = sf::RectangleShape(sf::Vector2f(C_SIZE, C_SIZE));
    this->rect.setFillColor(sf::Color(255, 0, 0));
    this->rect.setOrigin(C_HSIZE, C_HSIZE);
}
void Square::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}
void Square::Draw(sf::RenderWindow& window){
    window.draw(this->rect);
}
void Square::Update(){
    for (int i = 0; i < VELOCITY; i++){
        this->x += this->dx;
        this->y += this->dy;
    }
    this->rect.setPosition(this->x, this->y);
}