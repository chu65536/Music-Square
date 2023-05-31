#pragma once

class Square{
public:
    void setPosition(int x, int y);
    void setSpeed(int dx, int dy);
    void setStep(int step);
    void Init();
    int getX();
    int getY();
    int getStep();
    sf::RectangleShape getRect();
    void Draw(sf::RenderWindow& window);;

    void Collided();
    void Update(sf::Vector2f platform);
private:
    sf::RectangleShape rect;
    int x, y;
    int dx, dy;
    int step;
};
