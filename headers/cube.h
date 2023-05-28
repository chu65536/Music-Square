#pragma once

class Cube{
public:
    void setPosition(float x, float y);
    void setSpeed(float dx, float dy);
    void Collided();
    float getX();
    float getY();

    void Update();
private:
    float x, y;
    float dx, dy;
};
