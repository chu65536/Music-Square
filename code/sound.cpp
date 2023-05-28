#include "../headers/sound.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

sf::SoundBuffer buffer;
sf:: Sound sound;

void initSound(){
    buffer.loadFromFile("src/ding.wav");
    sound.setBuffer(buffer);
}
void PlaySound(float pitch){
    sound.setPitch(pitch);
    sound.play();
}