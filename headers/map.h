#pragma once

#include <vector>
#include "../headers/platform.h"
#include "../headers/square.h"

class Map{
    std::vector<sf::RectangleShape> background;
public:
    Map(Square& square);
    void build(float x, float y);
    void createBackground();
    void draw(sf::RenderWindow& window);

    std::vector<float> delays;
    std::vector<Platform> platforms;
    int pt;

};