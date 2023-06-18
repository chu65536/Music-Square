#pragma once

class Platform{
public:
    Platform(float x, float y, int dir);
    void draw(sf::RenderWindow& window);

    float x, y;
    int dir;
    sf::RectangleShape rect;
};