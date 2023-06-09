#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../headers/config.h"
#include "../headers/map.h"

sf::RectangleShape getDPlat(int x, int y){
    sf::RectangleShape platform;
    platform.setSize(sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
    platform.setOrigin(PLATFORM_WIDTH / 2, -C_HSIZE);

    return platform;
}
sf::RectangleShape getRPlat(int x, int y){
    sf::RectangleShape platform;
    platform.setSize(sf::Vector2f(PLATFORM_HEIGHT, PLATFORM_WIDTH));
    platform.setOrigin(-C_HSIZE, PLATFORM_WIDTH / 2);

    return platform;
}
sf::RectangleShape getUPlat(int x, int y){
    sf::RectangleShape platform;
    platform.setSize(sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
    platform.setOrigin(PLATFORM_WIDTH / 2, C_HSIZE + PLATFORM_HEIGHT);

    return platform;
}
sf::RectangleShape getLPlat(int x, int y){
    sf::RectangleShape platform;
    platform.setSize(sf::Vector2f(PLATFORM_HEIGHT, PLATFORM_WIDTH));
    platform.setOrigin(PLATFORM_HEIGHT + C_HSIZE, PLATFORM_WIDTH / 2);

    return platform;
}

Map::Map(int x, int y, std::vector<Platform> platforms){
    this->Build();
    this->createBackground();
}
void Map::Build(){
}
void Map::createBackground(){
}
void Map::Draw(sf::RenderWindow& window){
}