#pragma once

class Platform{
public:
    Platform(float x, float y, int dir, int frame);
    void draw(sf::RenderWindow& window);

    int frame;
    float x, y;
    int dir;
    sf::RectangleShape rect;
};