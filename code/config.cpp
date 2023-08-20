#include <iostream>
#include <fstream>
#include "../headers/config.hpp"

//default values
float Config::WINDOW_WIDTH = 800.f;
float Config::WINDOW_HEIGHT = 800.f;
float Config::VELOCITY_X = 200.f;
float Config::VELOCITY_Y = 200.f;
float Config::CAMERA_ZOOM = 0.5f;
float Config::CAMERA_SPEED = 3.f;
float Config::OFFSET = -0.12f;
float Config::FPS = 60.f;
float Config::SQUARE_SIZE = 20.f;
float Config::PLATFORM_WIDTH = Config::SQUARE_SIZE;
float Config::PLATFORM_HEIGHT = Config::SQUARE_SIZE / 2;
float Config::SQUARE_OUTLINE_THICKNESS = -2;
float Config::WALL_OUTLINE_THICKNESS = 2;
bool Config::FULLSCREEN = 0; 
bool Config::PROGRESS_BAR_LEFT = 0;
bool Config::COLORS_TO_NOTES = 1;
bool Config::SHOW_PROGRESS_BAR = 1;
bool Config::SIMPLE_MODE = 0;
sf::Color Config::SQUARE_COLOR = sf::Color(255, 0, 0);
sf::Color Config::PLATFORM_COLOR = sf::Color(0, 0, 0);
sf::Color Config::WALLS_COLOR = sf::Color(0, 0, 0);
sf::Color Config::BACKGROUND_COLOR = sf::Color(255, 255, 255);
sf::Color Config::SQUARE_OUTLINE_COLOR = sf::Color(0, 0, 0);
sf::Color Config::PROGRESS_BAR_COLOR = sf::Color(0, 0, 0);
sf::Color Config::WALL_OUTLINE_COLOR = sf::Color(0, 0, 0);



void Config::readConfig(){
    std::ifstream f("resources/config.ini");

    std::string param;
    if (f.is_open()){
        while(!f.eof()){
            float num;
            f >> param;
            f >> num;

            if (param == "WINDOW_WIDTH"){
                Config::WINDOW_WIDTH = num;
            }
            else if (param == "WINDOW_HEIGHT"){
                Config::WINDOW_HEIGHT = num;
            }
            else if (param == "VELOCITY_X"){
                Config::VELOCITY_X = num;
            }
            else if (param == "VELOCITY_Y"){
                Config::VELOCITY_Y = num;
            }
            else if (param == "CAMERA_ZOOM"){
                Config::CAMERA_ZOOM = num;
            }
            else if (param == "CAMERA_SPEED"){
                Config::CAMERA_SPEED = num;
            }
            else if (param == "OFFSET"){
                Config::OFFSET = num;
            }
            else if (param == "FPS"){
                Config::FPS = num;
            }
            else if (param == "SQUARE_COLOR"){
                float num2, num3;
                f >> num2 >> num3;
                Config::SQUARE_COLOR = sf::Color(num, num2, num3);
            }
            else if (param == "PLATFORM_COLOR"){
                float num2, num3;
                f >> num2 >> num3;
                Config::PLATFORM_COLOR = sf::Color(num, num2, num3);
            }
            else if (param == "WALLS_COLOR"){
                float num2, num3;
                f >> num2 >> num3;
                Config::WALLS_COLOR = sf::Color(num, num2, num3);
            }
            else if (param == "BACKGROUND_COLOR"){
                float num2, num3;
                f >> num2 >> num3;
                Config::BACKGROUND_COLOR = sf::Color(num, num2, num3);
            }
            else if (param == "SQUARE_SIZE"){
                Config::SQUARE_SIZE = num;
            }
            else if (param == "PLATFORM_HEIGHT"){
                Config::PLATFORM_HEIGHT = num;
            }
            else if (param == "PLATFORM_WIDTH"){
                Config::PLATFORM_WIDTH = num;
            }
            else if (param == "SQUARE_OUTLINE_COLOR"){
                float num2, num3;
                f >> num2 >> num3;
                Config::SQUARE_OUTLINE_COLOR = sf::Color(num, num2, num3);
            }
            else if (param == "SQUARE_OUTLINE_THICKNESS"){
                Config::SQUARE_OUTLINE_THICKNESS = num;
            }
            else if (param == "FULLSCREEN"){
                Config::FULLSCREEN = bool(num);
            }
            else if (param == "PROGRESS_BAR_LEFT"){
                Config::PROGRESS_BAR_LEFT = bool(num);
            }
            else if (param == "COLORS_TO_NOTES"){
                Config::COLORS_TO_NOTES = bool(num);
            }
            else if (param == "SHOW_PROGRESS_BAR"){
                Config::SHOW_PROGRESS_BAR = bool(num);
            }
            else if (param == "PROGRESS_BAR_COLOR"){
                float num2, num3;
                f >> num2 >> num3;
                Config::PROGRESS_BAR_COLOR = sf::Color(num, num2, num3);
            }
            else if (param == "SIMPLE_MODE"){
                Config::SIMPLE_MODE = bool(num);
            }
            else if (param == "WALL_OUTLINE_THICKNESS"){
                Config::WALL_OUTLINE_THICKNESS = num;
            }
            else if (param == "WALL_OUTLINE_COLOR"){
                float num2, num3;
                f >> num2 >> num3;
                Config::WALL_OUTLINE_COLOR = sf::Color(num, num2, num3);     
            }
            else{
                std::cout << "Error: " << param << " - wrong config parameter" << std::endl;
            } 
        }
        f.close();
    }
    else{
        std::cout << "Path error: cant find config.ini" << std::endl;
    }
}