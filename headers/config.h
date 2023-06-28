#pragma once

#include <SFML/Graphics.hpp>

class Config{
public:
    static void readConfig();
    static float WINDOW_WIDTH;
    static float WINDOW_HEIGHT;
    static float VELOCITY_X;
    static float VELOCITY_Y;
    static float CAMERA_ZOOM;
    static float CAMERA_BORDER;
    static float OFFSET;
    static float FPS;
    static float SQUARE_SIZE;
    static float PLATFORM_WIDTH;
    static float PLATFORM_HEIGHT;
    static float SQUARE_OUTLINE_THICKNESS;

    static sf::Color SQUARE_COLOR;
    static sf::Color PLATFORM_COLOR;
    static sf::Color WALLS_COLOR;
    static sf::Color BACKGROUND_COLOR;
    static sf::Color SQUARE_OUTLINE_COLOR;
};
