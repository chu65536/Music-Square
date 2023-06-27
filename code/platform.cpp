#include <SFML/Graphics.hpp>

#include "../headers/platform.h"
#include "../headers/config.h"


sf::RectangleShape getRect(float x, float y, int dir){
    sf::RectangleShape ret;
    ret.setPosition(sf::Vector2f(x, y));
    ret.setFillColor(sf::Color(PLATFORM_COLOR));
    if (dir == 0){
        ret.setSize(sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
        ret.setOrigin(PLATFORM_WIDTH / 2, -SQUARE_SIZE / 2);
    }
    if (dir == 1){
        ret.setSize(sf::Vector2f(PLATFORM_HEIGHT, PLATFORM_WIDTH));
        ret.setOrigin(-SQUARE_SIZE / 2, PLATFORM_WIDTH / 2);
    }
    if (dir == 2){
        ret.setSize(sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
        ret.setOrigin(PLATFORM_WIDTH / 2, SQUARE_SIZE / 2 + PLATFORM_HEIGHT);
    }
    if (dir == 3){
        ret.setSize(sf::Vector2f(PLATFORM_HEIGHT, PLATFORM_WIDTH));
        ret.setOrigin(PLATFORM_HEIGHT + SQUARE_SIZE / 2, PLATFORM_WIDTH / 2);
    }

    return ret;
}
Platform::Platform(float x, float y, int dir, int frame){
    this->x = x;
    this->y = y;
    this->dir = dir;
    this->frame = frame;

    this->rect = getRect(x, y, dir);
    this->rect.setFillColor(sf::Color(PLATFORM_COLOR));
}
void Platform::draw(sf::RenderWindow& window){
    window.draw(this->rect);
}
