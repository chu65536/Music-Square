#include <iostream>

#include "../headers/game.hpp"
#include "../headers/config.hpp"

Game::Game(){
    Config::readConfig();
    square = Square(0.f, 0.f, Config::VELOCITY_X, Config::VELOCITY_Y);
    map.build(square);
    float camera_w = Config::WINDOW_WIDTH * Config::CAMERA_ZOOM;
    float camera_h = Config::WINDOW_HEIGHT * Config::CAMERA_ZOOM;
    camera = Camera(0.f, 0.f, camera_w, camera_h);
    if (Config::FULLSCREEN)
        window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Music Square", sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Music Square");
    window.setVerticalSyncEnabled(true);

    progress_bar = ProgressBar(camera, map.delays[map.delays.size() - 1]);
    running = false;
    frame = 0;
    ellapsed_time = 0.f;

    colors.push_back(sf::Color(255, 0, 0)); // red
    colors.push_back(sf::Color(255, 135, 0)); // orange
    colors.push_back(sf::Color(255, 211, 0)); // light orange
    colors.push_back(sf::Color(222, 255, 10)); // yellow
    colors.push_back(sf::Color(161, 255, 10)); // light green
    colors.push_back(sf::Color(10, 255, 153)); // sea
    colors.push_back(sf::Color(10, 239, 255)); // cyan
    colors.push_back(sf::Color(20, 125, 245)); // light blue
    colors.push_back(sf::Color(88, 10, 255)); // blue
    colors.push_back(sf::Color(190, 10, 255)); // purple
}

void Game::playMusic(){
    music.play();
}

void Game::restart(){
    music.stop();
    map.pt = 0;
    square.x = map.platforms[0].x;
    square.y = map.platforms[0].y;
    square.rect.setPosition(square.x, square.y);
    square.velocity_x = Config::VELOCITY_X;
    square.velocity_y = Config::VELOCITY_Y;
    frame = 0;
    ellapsed_time = 0.f;
    running = false;
}

void Game::handleEvents(sf::Event event){
    // window close
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.key.code == sf::Keyboard::R){
        restart();
    }

    // keyboard
    if (event.type == sf::Event::KeyPressed){
        sf::Keyboard::Key key = event.key.code;
        switch(key){
            // play/pause
            case sf::Keyboard::Space: 
                playMusic();
                running= !running;
                break;
            // exit
            case sf::Keyboard::Escape:
                window.close();
                break;
        }
    }
}

float Game::getFrameTime(){
    return clock.restart().asSeconds();
}

void Game::update(float dt){
    if (running){
        while(frame == map.platforms[map.pt].frame){
            int dir = map.platforms[map.pt].dir;
            square.velocity_x *= (dir == 1 || dir == 3 ? -1 : 1);
            square.velocity_y *= (dir == 0 || dir == 2 ? -1 : 1);
            int color_id = map.notes[map.pt] % colors.size();
            if (Config::COLORS_TO_NOTES)
                square.rect.setFillColor(colors[color_id]);
            else
                square.rect.setFillColor(Config::SQUARE_COLOR);
            map.pt++;
        }
        ellapsed_time += dt;
        if (map.pt < map.delays.size()){
            frame++;
            square.update(dt);
        }
        else
            running = false;
    }
    square.shiftColor(dt);
    camera.update(square, dt);
    progress_bar.update(ellapsed_time);
}

void Game::draw(){
    window.setView(camera.view);
    window.clear(Config::WALLS_COLOR);
    if (Config::SIMPLE_MODE){
        map.drawPlatforms(window);
        map.drawBG(window);
        map.drawBGCover(window);
    }
    else{
        map.drawBGCover(window);
        map.drawPlatforms(window);
    }
    square.draw(window);
    window.draw(progress_bar.rect);
    window.display();
}