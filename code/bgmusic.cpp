#include <iostream>
#include <string>
#include <fstream>

#include "../headers/bgmusic.h"

std::string getPath(){
    std::string path = "";
    std::ifstream f("path.txt");
    if (f.is_open()){
        std::getline(f, path);
        path += ".ogg";
        f.close();
    }
    else{
        std::cout << "Path error: cant open music file" << std::endl;
    }

    return path;
}

BGMusic::BGMusic(){
    std::string path = getPath();
    this->is_loaded = 0;
    try{
        if (!this->music.openFromFile(path))
            throw "Music load error: Wrong path";
        this->is_loaded = 1;
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
}

void BGMusic::play(){
    if (this->is_loaded && this->music.getStatus() != sf::SoundSource::Playing)
        this->music.play();
}

float BGMusic::getOffset(){
    return this->music.getPlayingOffset().asSeconds();
}