#include <SFML/Graphics.hpp>
#include <vector>

#include "../headers/config.h"

std::vector<sf::RectangleShape> getMap(float x, float y, std::vector<float>& notes){
    std::vector<sf::RectangleShape> ret;

    float dx = DX * FPS;
    float dy = DY * FPS;
    int orientation = 1;
    for (int i = 0; i < notes.size(); i++){
        x += dx * notes[i];
        y += dy * notes[i] * orientation;

        sf::RectangleShape platform(sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT));
        if (orientation > 0)
            platform.setOrigin(sf::Vector2f(PLATFORM_WIDTH / 2.0f, -C_HSIZE));
        else{
            platform.setOrigin(sf::Vector2f(PLATFORM_WIDTH / 2.0f, PLATFORM_HEIGHT + C_HSIZE));
        }
        platform.setPosition(x, y);
        ret.push_back(platform);

        orientation *= -1;
    }

    return ret;
}