#include <SFML/Graphics.hpp>

#include "../headers/platform.hpp"
#include "../headers/config.hpp"


sf::RectangleShape getRect(float x, float y, int dir){
    sf::RectangleShape ret;
    ret.setPosition(sf::Vector2f(x, y));
    ret.setFillColor(sf::Color(Config::PLATFORM_COLOR));
    if (dir == 0){
        ret.setSize(sf::Vector2f(Config::PLATFORM_WIDTH, Config::PLATFORM_HEIGHT));
        ret.setOrigin(Config::PLATFORM_WIDTH / 2, -Config::SQUARE_SIZE / 2);
    }
    if (dir == 1){
        ret.setSize(sf::Vector2f(Config::PLATFORM_HEIGHT, Config::PLATFORM_WIDTH));
        ret.setOrigin(-Config::SQUARE_SIZE / 2, Config::PLATFORM_WIDTH / 2);
    }
    if (dir == 2){
        ret.setSize(sf::Vector2f(Config::PLATFORM_WIDTH, Config::PLATFORM_HEIGHT));
        ret.setOrigin(Config::PLATFORM_WIDTH / 2, Config::SQUARE_SIZE / 2 + Config::PLATFORM_HEIGHT);
    }
    if (dir == 3){
        ret.setSize(sf::Vector2f(Config::PLATFORM_HEIGHT, Config::PLATFORM_WIDTH));
        ret.setOrigin(Config::PLATFORM_HEIGHT + Config::SQUARE_SIZE / 2, Config::PLATFORM_WIDTH / 2);
    }

    return ret;
}
Platform::Platform(float x, float y, int dir, int frame){
    this->x = x;
    this->y = y;
    this->dir = dir;
    this->frame = frame;

    this->rect = getRect(x, y, dir);
    this->rect.setFillColor(sf::Color(Config::PLATFORM_COLOR));
}
void Platform::draw(sf::RenderWindow& window){
    window.draw(this->rect);
}
