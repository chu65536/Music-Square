#pragma once

#include<SFML/Audio.hpp>

class BGMusic{
    sf::Music music;
    bool is_loaded;
public:
    BGMusic();
    void play();
    float getOffset();
    std::string initParser();
};