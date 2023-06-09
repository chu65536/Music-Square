#pragma once

#include <vector>
#include "../headers/square.h"
#include "../headers/platform.h"

class Map{
public:
    Map(int x, int y, std::vector<Platform> platforms);
    void Build();
    void createBackground();
    void Draw(sf::RenderWindow& window);

private:

};