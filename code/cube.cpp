#include <iostream>

#include "../headers/cube.h"
#include "../headers/config.h"
#include "../headers/sound.h"

void Cube::setPosition(float x, float y){
    this->x = x;
    this->y = y;
}
void Cube::setSpeed(float dx, float dy){
    this->dx = dx;
    this->dy = dy;
}
void Cube::Collided(){
    this->dy *= -1;

    PlaySound(1.6f);
}
float Cube:: getX(){
    return this->x;
}
float Cube:: getY(){
    return this->y;
}
void Cube::Update(){
    this->x += this->dx;
    this->y += this->dy;

    // if(this->x > WINDOW_WIDTH - C_HSIZE && this->dx > 0){
    //     this->dx *= -1;
    //     PlaySound(0.7f);
    // }
    // if(this->x < C_HSIZE && this->dx < 0){
    //     this->dx *= -1;
    //     PlaySound(1.5f);
    // }
    // if(this->y > WINDOW_HEIGHT - C_HSIZE && this->dy > 0){
    //     this->dy *= -1;
    //     PlaySound(2.5f);
    // }
    // if(this->y < C_HSIZE&& this->dy < 0){
    //     this->dy *= -1;
    //     PlaySound(0.5f);
    // }
}