#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/square.h"
#include "../headers/config.h"
#include "../headers/sound.h"

void Square::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}
void Square::setSpeed(int dx, int dy){
    this->dx = dx;
    this->dy = dy;
}
void Square::setStep(int step){
    this->step = step;
}
void Square::Init(){
    this->setPosition(C_HSIZE, WINDOW_HEIGHT / 2);
    this->setSpeed(DX, DY);
    this->setStep(0);
    this->rect = sf::RectangleShape(sf::Vector2f(C_SIZE, C_SIZE));
    this->rect.setOrigin(C_HSIZE, C_HSIZE);
}
int Square::getX(){
    return this->x;
}
int Square::getY(){
    return this->y;
}
int Square::getStep(){
    return this->step;
}
sf::RectangleShape Square::getRect(){
    return this->rect;
}
void Square::Draw(sf::RenderWindow& window){
    this->rect.setFillColor(sf::Color(255, 0, 0));
    window.draw(this->rect);
}
void Square::Collided(){
    if (this->dx == this->dy)
        this->dy *= -1;
    else
        this->dx *= -1;

    this->step += 1;

    PlaySound(1.6f);
}
void Square::Update(sf::Vector2f platform){
    for (int i = 0; i < VELOCITY; i++){
        this->x += this->dx;
        this->y += this->dy;

        sf::Vector2f vec = sf::Vector2f(this->x, this->y);
        if (vec == platform)
            this->Collided();
    }
    this->rect.setPosition(this->x, this->y);
}