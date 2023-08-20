#define CUTE_C2_IMPLEMENTATION

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "../headers/config.hpp"
#include "../headers/map.hpp"
#include "../headers/cute_c2.hpp"

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

    int pt = 0;
    while(pt < delays.size() - 1){
        float dif = delays[pt + 1] - delays[pt];
        if (abs(dif) < 0.05f)
            delays.erase(delays.begin() + (pt + 1));
        else
            pt++;
    }
    float first = delays[0];
    for (int i = 0; i < delays.size(); i++)
        delays[i] -= first;

    for (auto i: delays)
        std::cout << i << '\n';
    
    return delays;
}

std::vector<int> getNotes(){
    std::vector<int> notes;
    std::ifstream f("resources/notes.txt");
    int val;
    if (f.is_open()){
        while (f >> val)
            notes.push_back(val);

        f.close();
    }
    else{
        std::cout << "Path error: cant open notes file" << std::endl;
    }
    return notes;
}

c2Poly getDanger(float x1, float y1, float x2, float y2){
    float ext = Config::SQUARE_SIZE;
    c2Poly ret;
    ret.count = 4;
    
    if (Config::SIMPLE_MODE){
        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);

        ret.verts[0] = c2V(x1 - ext / 2, y1 - ext / 2);
        ret.verts[1] = c2V(x2 + ext / 2, y1 - ext / 2);
        ret.verts[2] = c2V(x2 + ext / 2, y2 + ext / 2);
        ret.verts[3] = c2V(x1 - ext / 2, y2 + ext / 2);
    }
    else{
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


void Map::build(Square &square){
    float x = square.x;
    float y = square.y;
    pt = 0;
    delays = getDelays();
    notes = getNotes();
    
    platforms.push_back(Platform(x, y, 0, 0));

    int i = 1;
    float frame = 1.f / Config::FPS;
    std::vector<std::vector<int>> dirs(delays.size() + 1, std::vector<int>(2));
    dirs[1] = {1, 2};
    std::vector<c2Poly> dangers;
    std::vector<std::pair<int, int>> dxdy(delays.size() + 1);
    dxdy[0] = {1, 1};


    while(platforms.size() != delays.size()){
        if (i == 0){
            std::cout << "Error: cannot generate map. Unavoidable collisions\nTry to change configs\n";
            break;
        }
        if (dirs[i].size() == 0){
            platforms.pop_back();
            dangers.pop_back();
            i--;
            continue;    
        }
        std::cout << "Map generation: " << float(i) / delays.size() * 100 << '\n';
        float f_frame = delays[i] * Config::FPS;
        int cur_frame = int(f_frame);
        int prev_frame = platforms[i - 1].frame;
        int delta_frame = cur_frame - prev_frame;

        float cur_x = platforms[i - 1].x;
        float cur_y = platforms[i - 1].y;
        int dx = dxdy[i - 1].first;
        int dy = dxdy[i - 1].second;
        int prev_dir = platforms[i - 1].dir;
        dx *= (prev_dir == 1 || prev_dir == 3 ? -1 : 1);
        dy *= (prev_dir == 0 || prev_dir == 2 ? -1 : 1);
        cur_x += frame * delta_frame * Config::VELOCITY_X * dx;
        cur_y += frame * delta_frame * Config::VELOCITY_Y * dy;

        int pt = rand() % dirs[i].size();
        int dir = dirs[i][pt];
        dirs[i].erase(dirs[i].begin() + pt); 

        bool ok = true;
        float dang_x = platforms[i - 1].x;
        float dang_y = platforms[i - 1].y;
        c2Poly danger = getDanger(dang_x, dang_y, cur_x, cur_y);
        for (int j = 0; j < int(dangers.size()) - 1; j++){
            c2Poly plat = getPlat(cur_x, cur_y, dir);
            if (c2PolytoPoly(&plat, NULL, &dangers[j], NULL)){
                ok = false;
                break;
            }
        }
        for (int j = 0; j < int(platforms.size()) - 1; j++){
            c2Poly plat = getPlat(platforms[j].x, platforms[j].y, platforms[j].dir);
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

            platforms.push_back(Platform(cur_x, cur_y, dir, cur_frame));
        }
    }

    std::cout << "Done!\n";
    createBackground();
    createBackgroundCover();
}

void Map::createBackground(){
    for (size_t i = 1; i < platforms.size(); i++){
        float x1 = platforms[i - 1].x;
        float y1 = platforms[i - 1].y;
        float x2 = platforms[i].x;
        float y2 = platforms[i].y;
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
        back.setOutlineThickness(Config::WALL_OUTLINE_THICKNESS);
        back.setOutlineColor(Config::WALL_OUTLINE_COLOR);

        background.push_back(back);
    }
}

void Map::createBackgroundCover(){
    backgroundCover = background;
    for (auto &ret: backgroundCover){
        ret.setOutlineThickness(0);
    }
}

void Map::drawPlatforms(sf::RenderWindow& window){
    for (size_t i = 0; i < platforms.size(); i++){
        window.draw(platforms[i].rect);
    }
}

void Map::drawBG(sf::RenderWindow& window){
    for (size_t i = 0; i < background.size(); i++){
        window.draw(background[i]);
    }
}

void Map::drawBGCover(sf::RenderWindow& window){
    for (size_t i = 0; i < backgroundCover.size(); i++){
        window.draw(backgroundCover[i]);
    }
}