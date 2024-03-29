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
    static float CAMERA_SPEED;
    static float OFFSET;
    static float FPS;
    static float SQUARE_SIZE;
    static float PLATFORM_WIDTH;
    static float PLATFORM_HEIGHT;
    static float SQUARE_OUTLINE_THICKNESS;
    static float WALL_OUTLINE_THICKNESS;
    static bool FULLSCREEN;
    static bool PROGRESS_BAR_LEFT;
    static bool COLORS_TO_NOTES;
    static bool SHOW_PROGRESS_BAR;
    static bool SIMPLE_MODE;

    static sf::Color SQUARE_COLOR;
    static sf::Color PLATFORM_COLOR;
    static sf::Color WALLS_COLOR;
    static sf::Color BACKGROUND_COLOR;
    static sf::Color SQUARE_OUTLINE_COLOR;
    static sf::Color PROGRESS_BAR_COLOR;
    static sf::Color WALL_OUTLINE_COLOR;
};
