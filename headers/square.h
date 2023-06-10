#pragma once

#include "../headers/map.h"
#include "../headers/platform.h"

class Square{
public:
    Square(int x, int y, int dx, int dy);
    void setPosition(int x, int y);
    void Draw(sf::RenderWindow& window);
    void Collision(Platform platform);
    void Update(Map& map);

    int x, y;
    int dx, dy;
    sf::RectangleShape rect;
};
