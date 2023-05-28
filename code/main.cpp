#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "../headers/config.h"
#include "../headers/cube.h"
#include "../headers/sound.h"
#include "../headers/logic.h"

int main()
{   
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    sf::Clock clock;
    window.setFramerateLimit(FPS);
    

    Cube cube;
    cube.setSpeed(DX, DY);
    cube.setPosition(C_SIZE, WINDOW_HEIGHT / 2);
    sf::RectangleShape rect(sf::Vector2f(C_SIZE, C_SIZE));
    rect.setOrigin(C_HSIZE, C_HSIZE);

    initSound();

    //some melody
    std::vector<float> notes = 
    {0.1f, 0.8f, 0.6f, 0.4f, 0.4f, 0.2f, 0.4f, 0.2f, 0.2f,
    0.8f, 0.6f, 0.4f, 0.4f, 0.2f, 0.4f, 0.2f, 0.2f, 2.f};

    std::vector<sf::RectangleShape> map = getMap(cube.getX(), cube.getY(), notes);

    sf::View view(sf::FloatRect(0.f, 0.f, 400.f, 200.f));
    view.setCenter(cube.getX(), cube.getY());
    while (window.isOpen())
    {
        float current_time = clock.restart().asSeconds();
        float fps = 1.0f / (current_time);
        // std::cout << fps << '\n';

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.setView(view);

        for (int i = 0; i < map.size(); i++){
            window.draw(map[i]);
        }
        for (int i = 0; i < map.size(); i++){
            sf::Vector2f cube_pos = sf::Vector2f(cube.getX(), cube.getY());
            sf:: Vector2f platform_pos = map[i].getPosition();

            if (cube_pos == platform_pos)
                cube.Collided();
        }
        
        cube.Update();
        rect.setPosition(cube.getX(), cube.getY());
        window.draw(rect);
        view.setCenter(cube.getX(), cube.getY());

        window.display();
    }
}