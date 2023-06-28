#pragma once

class Square{
public:
    Square(float x, float y, float vel_x, float vel_y);
    void update(float time);
    void draw(sf::RenderWindow& window);

    float x, y;
    float velocity_x, velocity_y;
    sf::RectangleShape rect;
};
