#include <iostream>
#include <fstream>
#include "../headers/config.h"

//default values
float Config::WINDOW_WIDTH = 800.f;
float Config::WINDOW_HEIGHT = 800.f;
float Config::VELOCITY_X = 200.f;
float Config::VELOCITY_Y = 200.f;
float Config::CAMERA_ZOOM = 0.5f;
float Config::CAMERA_BORDER = 0.3f;
float Config::OFFSET = -0.12f;
float Config::FPS = 240.f;
float Config::SQUARE_SIZE = 20.f;
float Config::PLATFORM_WIDTH = Config::SQUARE_SIZE;
float Config::PLATFORM_HEIGHT = Config::SQUARE_SIZE / 2;
float Config::SQUARE_OUTLINE_THICKNESS = -2;
sf::Color Config::SQUARE_COLOR = sf::Color(255, 0, 0);
sf::Color Config::PLATFORM_COLOR = sf::Color(0, 0, 0);
sf::Color Config::WALLS_COLOR = sf::Color(0, 0, 0);
sf::Color Config::BACKGROUND_COLOR = sf::Color(255, 255, 255);
sf::Color Config::SQUARE_OUTLINE_COLOR = sf::Color(0, 0, 0);



void Config::readConfig(){
    std::ifstream f("src/config.ini");

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
            else if (param == "CAMERA_BORDER"){
                Config::CAMERA_BORDER = num;
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