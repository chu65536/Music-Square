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

void Map::createBackground(){
    int n = this->platforms.size();
    for (int i = 0; i < n - 1; i++){
        int width = abs(platforms[i].getPosition().x - platforms[i + 1].getPosition().x) + PLATFORM_WIDTH;
        int height = abs(platforms[i].getPosition().y - platforms[i + 1].getPosition().y) + C_SIZE;
        
        int x = (platforms[i].getPosition().x + platforms[i + 1].getPosition().x) / 2;
        int y = (platforms[i].getPosition().y + platforms[i + 1].getPosition().y) / 2;

        sf::RectangleShape back(sf::Vector2f(width, height));
        back.setFillColor(sf::Color(255, 255, 255));
        back.setOrigin(width / 2, height / 2);
        back.setPosition(x, y);

        this->background.push_back(back);
    }

    int width = abs(platforms[0].getPosition().x - platforms[n - 1].getPosition().x) + PLATFORM_WIDTH;
    int height = abs(platforms[0].getPosition().y - platforms[n - 1].getPosition().y) + C_SIZE;
    
    int x = (platforms[0].getPosition().x + platforms[n - 1].getPosition().x) / 2;
    int y = (platforms[0].getPosition().y + platforms[n - 1].getPosition().y) / 2;

    sf::RectangleShape back(sf::Vector2f(width, height));
    back.setFillColor(sf::Color(255, 255, 255));
    back.setOrigin(width / 2, height / 2);
    back.setPosition(x, y);

    this->background.push_back(back);
}

void Map::Build(Square& square, const std::vector<std::pair<int, int>>& notes){
    int x = square.getX();
    int y = square.getY();
    createPlatforms(x, y, notes);
    createBackground();
}

void Map::createPlatforms(int x, int y, const std::vector<std::pair<int, int>>& notes){
    int oy = 1;
    int ox = 1;

    int k = 1000 / (FPS * DX * VELOCITY); // should be int, otherwise not gonna work as intendent
    for (size_t i = 0; i < notes.size(); i++){
        int delay = notes[i].first;

        x += delay * ox / k; // same
        y += delay * oy / k; // same

        sf::RectangleShape platform;
        if (oy > 0 && ox > 0){
            platform = getDPlat(x, y);
        }
        else if (oy < 0 && ox > 0){
            platform = getRPlat(x, y);
        }
        else if (oy > 0 && ox < 0){
            platform = getLPlat(x, y);
        }
        else{
            platform = getUPlat(x, y);
        }
        platform.setPosition(sf::Vector2f(x, y));
        platform.setFillColor(sf::Color(200, 200, 200));
        if (ox == oy)
            oy *= -1;
        else
            ox *= -1;
        this->platforms.push_back(platform);
    }
}
void Map::Draw(sf::RenderWindow& window){
    for (size_t i = 0; i < this->platforms.size(); i++){
        window.draw(platforms[i]);
    }
    for (size_t i = 0; i < this->background.size(); i++)
        window.draw(background[i]);
}
sf::Vector2f Map::getPlatform(int id){
    return this->platforms[id].getPosition();
}