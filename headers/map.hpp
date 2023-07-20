#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../headers/platform.hpp"
#include "../headers/square.hpp"

class Map{
    std::vector<sf::RectangleShape> background;
public:
    void build(float x, float y);
    void createBackground();
    void drawPlatforms(sf::RenderWindow& window);
    void drawBG(sf::RenderWindow& window);

    std::vector<float> delays;
    std::vector<Platform> platforms;
    int pt;

};