#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <deque>

#define WINDOW_HEIHT 500
#define WINDOW_WIDTH 1000

using namespace sf;
using namespace std;

void SetBackground(vector<RectangleShape>& rectangles){
    float rectangle_height = WINDOW_HEIHT / 10;
    float rectangle_width = WINDOW_WIDTH / 10;
    
    float R = rand() % 256, G = rand() % 256, B = rand() % 256;
    float color_k = 1.0 / (WINDOW_HEIHT + WINDOW_WIDTH);
    for (float i = 0.0; i < WINDOW_WIDTH; i += rectangle_width)
        for (float j = 0.0; j < WINDOW_HEIHT; j += rectangle_height){
            float k = (i + j)*color_k;
            RectangleShape rec(Vector2f(rectangle_width, rectangle_height));
            Color col = Color(R*k, G*k, B*k);
            rec.setFillColor(col);
            rec.setPosition(i, j);
            rectangles.push_back(rec);
        }

    return;
}

void DrawBackground(const vector<RectangleShape>& rectangles, RenderWindow& window){
    for (RectangleShape i: rectangles)
        window.draw(i);
}

class Player{
public:
    float x, y;

    Player(float x, float y){
        this->x = x;
        this->y = y;
    }
};

int main()
{   
    srand(time(0));
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIHT), "SFML works!");

    vector<RectangleShape> rectangles;
    SetBackground(rectangles);

    Player player(0.0f, 0.0f);

    Clock clock;
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        float current_time = clock.restart().asSeconds();
        float fps = 1.0f / (current_time);
        //cout << fps << '\n';

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        DrawBackground(rectangles, window);
        window.display();
    }

    return 0;
}