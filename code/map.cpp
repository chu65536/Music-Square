#define CUTE_C2_IMPLEMENTATION

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "../headers/config.h"
#include "../headers/map.h"
#include "../headers/cute_c2.h"

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

    int pt = 1;
    while(pt < delays.size()){
        float dif = delays[pt] - delays[pt-1];
        if (abs(dif) < 0.05f)
            delays.erase(delays.begin() + (pt - 1));
        else
            pt++;
    }
    return delays;
}

c2Poly getDanger(float x1, float y1, float x2, float y2){
    float ext = Config::SQUARE_SIZE;
    c2Poly ret;
    ret.count = 4;
    
    if (x1 < x2){
        ret.verts[0] = c2V(x1 - ext, y1);
        ret.verts[2] = c2V(x2 + ext, y2);
    }
    else{
        ret.verts[0] = c2V(x2 - ext, y2);
        ret.verts[2] = c2V(x1 + ext, y1); 
    }
    if(y1 < y2){
        ret.verts[1] = c2V(x1, y1 - ext);
        ret.verts[3] = c2V(x2, y2 + ext);
    }
    else{
        ret.verts[1] = c2V(x2, y2 - ext);
        ret.verts[3] = c2V(x1, y1 + ext);   
    }
    
    return ret;
}

c2Poly getPlat(float x, float y, int dir){
    c2Poly ret;
    ret.count = 4;
    
    float square_sz = Config::SQUARE_SIZE;
    float plat_width = Config::PLATFORM_WIDTH;
    float plat_height = Config::PLATFORM_HEIGHT;
    if (dir == 0){
        ret.verts[0] = c2V(x - plat_width / 2, y + square_sz / 2);
        ret.verts[1] = c2V(x + plat_width / 2, y + square_sz / 2);
        ret.verts[2] = c2V(x + plat_width / 2, y + square_sz / 2 + plat_height);
        ret.verts[3] = c2V(x - plat_width / 2, y + square_sz / 2 + plat_height);
    }
    if (dir == 1){
        ret.verts[0] = c2V(x + square_sz / 2, y + plat_width / 2);
        ret.verts[1] = c2V(x + square_sz / 2, y - plat_width / 2);
        ret.verts[2] = c2V(x + square_sz / 2 + plat_height, y - plat_width / 2);
        ret.verts[3] = c2V(x + square_sz / 2 + plat_height, y + plat_width / 2);
    }
    if (dir == 2){
        ret.verts[0] = c2V(x + plat_width / 2, y - square_sz / 2);
        ret.verts[1] = c2V(x - plat_width / 2, y - square_sz / 2);
        ret.verts[2] = c2V(x - plat_width / 2, y - square_sz / 2 - plat_height);
        ret.verts[3] = c2V(x + plat_width / 2, y - square_sz / 2 - plat_height);
    }
    if (dir == 3){
        ret.verts[0] = c2V(x - square_sz / 2, y - plat_width / 2);
        ret.verts[1] = c2V(x - square_sz / 2, y + plat_width / 2);
        ret.verts[2] = c2V(x - square_sz / 2 - plat_height, y + plat_width / 2);
        ret.verts[3] = c2V(x - square_sz / 2 - plat_height, y - plat_width / 2);
    }
    return ret;
}


void Map::build(float x, float y){
    this->pt = 0;
    this->delays = getDelays();
    
    this->platforms.push_back(Platform(x, y, 0, 0));

    int i = 1;
    float frame = 1.f / Config::FPS;
    std::vector<std::vector<int>> dirs(this->delays.size() + 1, std::vector<int>(2));
    dirs[1] = {1, 2};
    std::vector<c2Poly> dangers;
    std::vector<std::pair<int, int>> dxdy(this->delays.size() + 1);
    dxdy[0] = {1, 1};


    while(this->platforms.size() != this->delays.size()){
        if (i == 0){
            std::cout << "Error: cannot generate map. Unavoidable collisions\nTry to change configs\n";
            break;
        }
        if (dirs[i].size() == 0){
            this->platforms.pop_back();
            dangers.pop_back();
            i--;
            continue;    
        }
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

        int pt = rand() % dirs[i].size();
        int dir = dirs[i][pt];
        dirs[i].erase(dirs[i].begin() + pt); 

        bool ok = true;
        float dang_x = this->platforms[i - 1].x;
        float dang_y = this->platforms[i - 1].y;
        c2Poly danger = getDanger(dang_x, dang_y, cur_x, cur_y);
        for (int j = 0; j < int(dangers.size()) - 1; j++){
            c2Poly plat = getPlat(cur_x, cur_y, dir);
            if (c2PolytoPoly(&plat, NULL, &dangers[j], NULL)){
                ok = false;
                break;
            }
        }
        for (int j = 0; j < int(this->platforms.size()) - 1; j++){
            c2Poly plat = getPlat(this->platforms[j].x, this->platforms[j].y, this->platforms[j].dir);
            if (c2PolytoPoly(&plat, NULL, &danger, NULL)){
                ok = false; 
                break;
            }
        }

        if (ok){
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
    }

    std::cout << "Done!\n";
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