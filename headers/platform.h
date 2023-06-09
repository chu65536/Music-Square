#pragma once

class Platform{
public:
    void setPosition(int x, int y);
    int getX();
    int getY();
    void Draw(sf::RenderWindow& window);;

private:
    int x, y;
};