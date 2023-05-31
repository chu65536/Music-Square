#pragma once

#include "../headers/square.h"

class Map{
public:
    void Build(Square& square, const std::vector<std::pair<int, int>>& notes);
    void createPlatforms(int x, int y, const std::vector<std::pair<int, int>>& notes);
    void createBackground();
    void Draw(sf::RenderWindow& window);
    sf::Vector2f getPlatform(int id);

    std::vector<sf::RectangleShape> platforms;
private:
    std::vector<sf::RectangleShape> background;    
};