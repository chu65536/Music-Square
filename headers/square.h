#pragma once

class Square{
public:
    Square(int x, int y, int dx, int dy);
    void setPosition(int x, int y);
    void Draw(sf::RenderWindow& window);;
    void Update();

    int x, y;
    int dx, dy;
    sf::RectangleShape rect;
};
