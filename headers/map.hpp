#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../headers/platform.hpp"
#include "../headers/square.hpp"

class Map{
    std::vector<sf::RectangleShape> background;
    std::vector<sf::RectangleShape> backgroundCover;
public:
    void build(Square &square);
    void createBackground();
    void createBackgroundCover();
    void drawPlatforms(sf::RenderWindow& window);
    void drawBG(sf::RenderWindow& window);
    void drawBGCover(sf::RenderWindow& window);

    std::vector<float> delays;
    std::vector<int> notes;
    std::vector<Platform> platforms;
    int pt;

};