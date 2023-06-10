#pragma once

class Platform{
public:
    Platform(int x, int y, int dir);
    void Draw(sf::RenderWindow& window);

    int x, y;
    int dir;
    sf::RectangleShape rect;
};