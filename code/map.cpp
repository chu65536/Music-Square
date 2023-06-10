#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../headers/config.h"
#include "../headers/map.h"

Map::Map(int x, int y, std::vector<std::pair<int, int>> notes){
    this->Build(x, y, notes);
    this->createBackground();
    this->pt = 0;
}
void Map::Build(int x, int y, std::vector<std::pair<int, int>> notes){
    int dx = 1, dy = 1;
    for (size_t i = 0; i < notes.size(); i++){
        x += dx * DX * notes[i].first / 10;
        y += dy * DY * notes[i].first / 10; 

        if (i % 6 == 0){
            this->platforms.push_back(Platform(x, y, 0));
            dy *= -1;
        }
        if (i % 6 == 1){
            this->platforms.push_back(Platform(x, y, 2));
            dy *= -1;
        }
        if (i % 6 == 2){
            this->platforms.push_back(Platform(x, y, 0));
            dy *= -1;
        }
        if (i % 6 == 3){
            this->platforms.push_back(Platform(x, y, 1));
            dx *= -1;
        }
        if (i % 6 == 4){
            this->platforms.push_back(Platform(x, y, 3));
            dx *= -1;       
        }
        if (i % 6 == 5){
            this->platforms.push_back(Platform(x, y, 2));
            dy *= -1;
        }
    }
}
void Map::createBackground(){
    for (size_t i = 1; i < this->platforms.size(); i++){

        int x1 = this->platforms[i - 1].x;
        int y1 = this->platforms[i - 1].y;
        int x2 = this->platforms[i].x;
        int y2 = this->platforms[i].y;
        int x = std::min(x1, x2);
        int y = std::min(y1, y2);

        int w = abs(x1 - x2);
        int h = abs(y1 - y2);

        if (platforms[i - 1].dir == 1 || platforms[i - 1].dir == 3){
            w += C_HSIZE;
            h += PLATFORM_WIDTH / 2;

            if (x1 < x2)
                x -= C_HSIZE;
            if (y1 < y2)
                y -= PLATFORM_WIDTH / 2;
        }
        else{
            w += PLATFORM_WIDTH / 2;
            h += C_HSIZE;

            if (x1 < x2)
                x -= PLATFORM_WIDTH / 2;
            if (y1 < y2)
                y -= C_HSIZE;
        }
        if (platforms[i].dir == 1 || platforms[i].dir == 3){
            w += C_HSIZE;
            h += PLATFORM_WIDTH / 2;

            if (x2 < x1)
                x -= C_HSIZE;
            if (y2 < y1)
                y -= PLATFORM_WIDTH / 2;
        }
        else{
            w += PLATFORM_WIDTH / 2;
            h += C_HSIZE;

            if (x2 < x1)
                x -= PLATFORM_WIDTH / 2;
            if (y2 < y1)
                y -= C_HSIZE;
        }

        sf::RectangleShape back = sf::RectangleShape(sf::Vector2f(w, h));
        back.setPosition(sf::Vector2f(x, y));
        back.setFillColor(BACKGROUND_COLOR);

        this->background.push_back(back);
    }
}
void Map::Draw(sf::RenderWindow& window){
    for (size_t i = 0; i < this->background.size(); i++){
        window.draw(this->background[i]);
    }
    for (size_t i = 0; i < this->platforms.size(); i++){
        window.draw(this->platforms[i].rect);
    }
}