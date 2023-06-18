#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "../headers/config.h"
#include "../headers/map.h"

std::vector<float> getDelays(){
    std::vector<float> delays;
    std::ifstream f("delays.txt");
    float val;
    if (f.is_open()){
        while (f >> val)
            delays.push_back(val);

        f.close();
    }
    else{
        std::cout << "Path error: cant open delays file" << std::endl;
    }

    return delays;
}

Map::Map(Square& square){
    this->delays = getDelays();
    this->build(square.x, square.y);
    this->createBackground();
}

void Map::build(float x, float y){
    int dy = 1;
    float prev = 0.f;
    for (size_t i = 0; i < this->delays.size(); i++){
        float cur = delays[i] - prev;
        prev = delays[i];
        x += cur * VELOCITY_X;
        y += cur * VELOCITY_Y * dy;

        if (dy == 1)
            this->platforms.push_back(Platform(x, y, 0));
        else
            this->platforms.push_back(Platform(x, y, 2));
        dy *= -1;
    }
}

void Map::createBackground(){
}

void Map::draw(sf::RenderWindow& window){
    for (size_t i = 0; i < this->background.size(); i++){
        window.draw(this->background[i]);
    }
    for (size_t i = 0; i < this->platforms.size(); i++){
        window.draw(this->platforms[i].rect);
    }
}