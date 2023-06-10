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
    this->rect.setFillColor(SQUARE_COLOR);
    this->rect.setOrigin(C_HSIZE, C_HSIZE);
}
void Square::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}
void Square::Draw(sf::RenderWindow& window){
    window.draw(this->rect);
}
void Square::Collision(Platform platform){
    if (platform.dir == 0 || platform.dir == 2)
        this->dy *= -1;
    else
        this->dx *= -1;

    PlaySound(1.5f);
}
void Square::Update(Map& map){
    for (int i = 0; i < FRAMES; i++){
        this->x += this->dx;
        this->y += this->dy;

        if (sf::Vector2f(x, y) == map.platforms[map.pt].rect.getPosition()){
            this->Collision(map.platforms[map.pt]);
            map.pt++;
            map.pt %= map.platforms.size();
        }
    }
    this->rect.setPosition(this->x, this->y);
}