#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "../headers/config.h"
#include "../headers/map.h"

std::vector<float> getDelays(){
    std::vector<float> delays;
    std::ifstream f("src/delays.txt");
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
    this->createBGCover();
    this->pt = 0;
}

void Map::build(float x, float y){
    this->platforms.push_back(Platform(x, y, 2, 0));
    int prev_frame = 0;

    int dx = 1, dy = 1;
    int dir = 0;
    for (size_t i = 1; i < this->delays.size(); ++i){
        float f_frame = this->delays[i] * FPS;
        int cur_frame;
        if (std::ceil(f_frame) - f_frame < f_frame - std::floor(f_frame))
            cur_frame = int(f_frame + 1);
        else
            cur_frame = int(f_frame);

        int delta_frame = cur_frame - prev_frame;
        prev_frame = cur_frame;

        float frame = 1.f / FPS;
        x += frame * delta_frame * VELOCITY_X * dx;
        y += frame * delta_frame * VELOCITY_Y * dy;

        this->platforms.push_back(Platform(x, y, dir, cur_frame));
        dy *= -1;
        dir = (dir + 2) % 4;
    }
}

void Map::createBackground(){
    for (size_t i = 1; i < this->platforms.size(); i++){
        float x1 = this->platforms[i - 1].x;
        float y1 = this->platforms[i - 1].y;
        float x2 = this->platforms[i].x;
        float y2 = this->platforms[i].y;
        float x = std::min(x1, x2);
        float y = std::min(y1, y2);

        float w = x1 - x2;
        float h = y1 - y2;
        if (w < 0)
            w = -w;
        if (h < 0)
            h = -h;

        if (platforms[i - 1].dir == 1 || platforms[i - 1].dir == 3){
            w += SQUARE_SIZE / 2;
            h += PLATFORM_WIDTH / 2;

            if (x1 < x2)
                x -= SQUARE_SIZE / 2;
            if (y1 < y2)
                y -= PLATFORM_WIDTH / 2;
        }
        else{
            w += PLATFORM_WIDTH / 2;
            h += SQUARE_SIZE / 2;

            if (x1 < x2)
                x -= PLATFORM_WIDTH / 2;
            if (y1 < y2)
                y -= SQUARE_SIZE / 2;
        }
        if (platforms[i].dir == 1 || platforms[i].dir == 3){
            w += SQUARE_SIZE / 2;
            h += PLATFORM_WIDTH / 2;

            if (x2 < x1)
                x -= SQUARE_SIZE / 2;
            if (y2 < y1)
                y -= PLATFORM_WIDTH / 2;
        }
        else{
            w += PLATFORM_WIDTH / 2;
            h += SQUARE_SIZE / 2;

            if (x2 < x1)
                x -= PLATFORM_WIDTH / 2;
            if (y2 < y1)
                y -= SQUARE_SIZE / 2;
        }

        sf::RectangleShape back = sf::RectangleShape(sf::Vector2f(w, h));
        back.setPosition(sf::Vector2f(x, y));
        back.setFillColor(sf::Color(BACKGROUND_COLOR));
        //back.setOutlineThickness(WALLS_OUTLINE_THICKNESS);
        //back.setOutlineColor(sf::Color(WALLS_OUTLINE_COLOR));

        this->background.push_back(back);
    }
}

void Map::createBGCover(){
    for (size_t i = 0; i < this->background.size(); i++){ 
        sf::RectangleShape cur;
        cur = background[i];
        cur.setOutlineThickness(0);
        this->bg_cover.push_back(cur);
    }
}

void Map::drawPlatforms(sf::RenderWindow& window){
    for (size_t i = 0; i < this->platforms.size(); i++){
        window.draw(this->platforms[i].rect);
    }
}
void Map::drawBG(sf::RenderWindow& window){
    for (size_t i = 0; i < this->background.size(); i++){
        window.draw(this->background[i]);
    }
}