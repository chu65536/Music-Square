#include <SFML/Graphics.hpp>

#include "../headers/platform.h"
#include "../headers/config.h"


sf::RectangleShape getRect(int x, int y, int dir){
    sf::RectangleShape ret;
    ret.setPosition(sf::Vector2f(x, y));
    ret.setFillColor(PLATFORM_COLOR);
    if (dir == 0){
        ret.setSize(sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
        ret.setOrigin(PLATFORM_WIDTH / 2, -C_HSIZE);
    }
    if (dir == 1){
        ret.setSize(sf::Vector2f(PLATFORM_HEIGHT, PLATFORM_WIDTH));
        ret.setOrigin(-C_HSIZE, PLATFORM_WIDTH / 2);
    }
    if (dir == 2){
        ret.setSize(sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
        ret.setOrigin(PLATFORM_WIDTH / 2, C_HSIZE + PLATFORM_HEIGHT);
    }
    if (dir == 3){
        ret.setSize(sf::Vector2f(PLATFORM_HEIGHT, PLATFORM_WIDTH));
        ret.setOrigin(PLATFORM_HEIGHT + C_HSIZE, PLATFORM_WIDTH / 2);
    }

    return ret;
}
Platform::Platform(int x, int y, int dir){
    this->x = x;
    this->y = y;
    this->dir = dir;

    this->rect = getRect(x, y, dir);
}
void Platform::Draw(sf::RenderWindow& window){
    window.draw(this->rect);
}
