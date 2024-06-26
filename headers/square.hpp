#pragma once

class Square{
public:
    Square(float x = 0.f, float y = 0.f, float vel_x = 250.f, float vel_y = 250.f);
    void update(float time);
    void draw(sf::RenderWindow& window);
    void shiftColor(float dt);

    float x, y;
    float velocity_x, velocity_y;
    float cycled_dx, cycled_dy;
    sf::RectangleShape rect;
};
