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
    if (Config::FULLSCREEN)
        this->window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Music Square", sf::Style::Fullscreen);
    else
        this->window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Music Square");
    this->window.setVerticalSyncEnabled(true);

    this->progress_bar = ProgressBar(this->camera, this->map.delays[map.delays.size() - 1]);
    this->running = false;
    this->frame = 0;
    this->ellapsed_time = 0.f;
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

float Game::getFrameTime(){
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
        ellapsed_time += dt;
        if (this->map.pt < this->map.delays.size()){
            this->frame++;
            this->square.update(dt);
        }
        else
            this->running = false;
    }
    this->camera.update(this->square, dt);
    this->progress_bar.update(ellapsed_time);
}

void Game::draw(){
    this->window.setView(this->camera.view);
    this->window.clear(Config::WALLS_COLOR);
    this->map.drawBG(this->window);
    this->map.drawPlatforms(this->window);
    this->square.draw(this->window);
    this->window.draw(progress_bar.rect);
    this->window.display();
}