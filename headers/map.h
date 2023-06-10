#pragma once

#include <vector>
#include "../headers/platform.h"

class Map{
public:
    Map(int x, int y, std::vector<std::pair<int, int>> notes);
    void Build(int x, int y, std::vector<std::pair<int, int>> notes);
    void createBackground();
    void Draw(sf::RenderWindow& window);

    std::vector<Platform> platforms;
    int pt;
private:
    std::vector<sf::RectangleShape> background;
};