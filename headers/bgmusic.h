#pragma once

#include <SFML/Audio.hpp>

class BGMusic{
    sf::Music music;
    bool is_loaded;
public:
    BGMusic();
    void play();
    void stop();
    float getOffset();
    std::string initParser();
};