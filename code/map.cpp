#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "../headers/config.h"
#include "../headers/map.h"

std::vector<float> getDelays(){
    std::vector<float> delays;
    std::ifstream f("resources/delays.txt");
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

void Map::build(float x, float y){
    this->pt = 0;
    this->delays = getDelays();
    
    this->platforms.push_back(Platform(x, y, 0, 0));

    int i = 1;
    float frame = 1.f / Config::FPS;
    std::vector<std::vector<int>> dirs(this->delays.size() + 1, std::vector<int>(2));
    dirs[1] = {1, 2};
    std::vector<sf::RectangleShape> dangers;
    std::vector<std::pair<int, int>> dxdy(this->delays.size() + 1);
    dxdy[0] = {1, 1};


    while(this->platforms.size() != this->delays.size()){
        std::cout << "Map generation: " << float(i) / this->delays.size() * 100 << '\n';
        float f_frame = this->delays[i] * Config::FPS;
        int cur_frame;
        if (std::ceil(f_frame) - f_frame < f_frame - std::floor(f_frame))
            cur_frame = int(f_frame + 1);
        else
            cur_frame = int(f_frame);

        int prev_frame = this->platforms[i - 1].frame;
        int delta_frame = cur_frame - prev_frame;

        float cur_x = this->platforms[i - 1].x;
        float cur_y = this->platforms[i - 1].y;
        int dx = dxdy[i - 1].first;
        int dy = dxdy[i - 1].second;
        int prev_dir = this->platforms[i - 1].dir;
        dx *= (prev_dir == 1 || prev_dir == 3 ? -1 : 1);
        dy *= (prev_dir == 0 || prev_dir == 2 ? -1 : 1);
        cur_x += frame * delta_frame * Config::VELOCITY_X * dx;
        cur_y += frame * delta_frame * Config::VELOCITY_Y * dy;


        bool ok = true;
        int sz = dangers.size();
        float ext = Config::SQUARE_SIZE * 1.5f;
        for (int j = 0; j < sz - 1; j++){
            float danger_x1 = dangers[j].getPosition().x - ext;
            float danger_x2 = danger_x1 + dangers[j].getSize().x + ext;
            float danger_y1 = dangers[j].getPosition().y - ext;
            float danger_y2 = danger_y1 + dangers[j].getSize().y + ext;
            if ((danger_x1 < cur_x && cur_x < danger_x2) && (danger_y1 < cur_y && cur_y < danger_y2)){
                ok = false;
                break;
            }
        }

        float tmp_w = abs(cur_x - this->platforms[i - 1].x);
        float tmp_h = abs(cur_y - this->platforms[i - 1].y);
        float tmp_x1 = std::min(cur_x, this->platforms[i - 1].x) - ext;
        float tmp_y1 = std::min(cur_y, this->platforms[i - 1].y) - ext;;
        float tmp_x2 = tmp_x1 + tmp_w + ext * 2;
        float tmp_y2 = tmp_y1 + tmp_h + ext * 2;
        for (int j = 0; j < int(this->platforms.size()) - 1; j++){
            float plat_x = this->platforms[j].x;
            float plat_y = this->platforms[j].y;

            if ((tmp_x1 < plat_x && plat_x < tmp_x2) && (tmp_y1 < plat_y && plat_y < tmp_y2)){
                ok = false;
                break;
            }
        }

        if (ok && !dirs[i].empty()){
            int pt = rand() % dirs[i].size();
            int dir = dirs[i][pt];
            dirs[i].erase(dirs[i].begin() + pt);
            float danger_w = abs(cur_x - this->platforms[i - 1].x);
            float danger_h = abs(cur_y - this->platforms[i - 1].y);
            float danger_x = std::min(cur_x, this->platforms[i - 1].x);
            float danger_y = std::min(cur_y, this->platforms[i - 1].y);
            sf::RectangleShape danger(sf::Vector2f(danger_w, danger_h));
            danger.setPosition(danger_x, danger_y);
            dangers.push_back(danger);
            dxdy[i] = {dx, dy};

            dx *= (dir == 1 || dir == 3 ? -1 : 1);
            dy *= (dir == 0 || dir == 2 ? -1 : 1);
            std::vector<int> new_dirs;
            if (dx > 0 && dy > 0)
                new_dirs = {0, 1};
            if (dx > 0 && dy < 0)
                new_dirs = {1, 2};
            if (dx < 0 && dy > 0)
                new_dirs = {0, 3};
            if (dx < 0 && dy < 0)
                new_dirs = {2, 3};
            i++;
            dirs[i] = new_dirs;

            this->platforms.push_back(Platform(cur_x, cur_y, dir, cur_frame));
        }
        else{
            this->platforms.pop_back();
            dangers.pop_back();
            i--;
        }
    }

    if (this->platforms.size() == this->delays.size())
        std::cout << "Map generated successufully!\n";
    else
        std::cout << "Cannot generate map. Try to config square speed\n";
    this->createBackground();
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
            w += Config::SQUARE_SIZE / 2;
            h += Config::PLATFORM_WIDTH / 2;

            if (x1 < x2)
                x -= Config::SQUARE_SIZE / 2;
            if (y1 < y2)
                y -= Config::PLATFORM_WIDTH / 2;
        }
        else{
            w += Config::PLATFORM_WIDTH / 2;
            h += Config::SQUARE_SIZE / 2;

            if (x1 < x2)
                x -= Config::PLATFORM_WIDTH / 2;
            if (y1 < y2)
                y -= Config::SQUARE_SIZE / 2;
        }
        if (platforms[i].dir == 1 || platforms[i].dir == 3){
            w += Config::SQUARE_SIZE / 2;
            h += Config::PLATFORM_WIDTH / 2;

            if (x2 < x1)
                x -= Config::SQUARE_SIZE / 2;
            if (y2 < y1)
                y -= Config::PLATFORM_WIDTH / 2;
        }
        else{
            w += Config::PLATFORM_WIDTH / 2;
            h += Config::SQUARE_SIZE / 2;

            if (x2 < x1)
                x -= Config::PLATFORM_WIDTH / 2;
            if (y2 < y1)
                y -= Config::SQUARE_SIZE / 2;
        }

        sf::RectangleShape back = sf::RectangleShape(sf::Vector2f(w, h));
        back.setPosition(sf::Vector2f(x, y));
        back.setFillColor(sf::Color(Config::BACKGROUND_COLOR));

        this->background.push_back(back);
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