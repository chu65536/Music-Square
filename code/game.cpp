#include <iostream>

#include "../headers/game.h"
#include "../headers/config.h"

Game::Game(){
    Config::readConfig();
    this->square = Square(0.f, 0.f, Config::VELOCITY_X, Config::VELOCITY_Y);
    this->map.build(this->square.x, this->square.y);
    float camera_w = Config::WINDOW_WIDTH * Config::CAMERA_ZOOM;
    float camera_h = Config::WINDOW_HEIGHT * Config::CAMERA_ZOOM;
    this->camera = Camera(0.f, 0.f, camera_w, camera_h);
    this->window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Music Square");
    this->window.setVerticalSyncEnabled(true);

    this->running = false;
    this->frame = 0;
}

void Game::playMusic(){
    this->music.play();
}

void Game::handleEvents(sf::Event event){
    // window close
    if (event.type == sf::Event::Closed)
        window.close();

    // keyboard
    if (event.type == sf::Event::KeyPressed){
        sf::Keyboard::Key key = event.key.code;
        switch(key){
            // play/pause
            case sf::Keyboard::Space: 
                this->playMusic();
                this->running= !this->running;
                break;
            // exit
            case sf::Keyboard::Escape:
                this->window.close();
                break;
        }
    }
}

float Game::getEllapsedTime(){
    return this->clock.restart().asSeconds();
}

void Game::update(float dt){
    if (this->running){
        while(this->frame == this->map.platforms[map.pt].frame){
            int dir = this->map.platforms[map.pt].dir;
            this->square.velocity_x *= (dir == 1 || dir == 3 ? -1 : 1);
            this->square.velocity_y *= (dir == 0 || dir == 2 ? -1 : 1);
            this->map.pt++;
        }
        if (this->map.pt < this->map.delays.size()){
            this->frame++;
            this->square.update(dt);
        }
    }
    this->camera.update(this->square);
}

void Game::draw(){
    this->window.setView(this->camera.view);

    this->window.clear(Config::WALLS_COLOR);
    this->map.drawBG(this->window);
    this->map.drawPlatforms(this->window);
    this->square.draw(this->window);
    this->window.display();
}