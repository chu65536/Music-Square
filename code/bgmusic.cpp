#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <tchar.h>

#include "../headers/bgmusic.h"

std::string BGMusic::initParser(){
    STARTUPINFO si = {sizeof(STARTUPINFO)};
    PROCESS_INFORMATION pi;
    CreateProcess(_T("parser/midi_parser.exe"), NULL, 0, 0, 0, 0, 0, 0, &si, &pi);
;
    WaitForSingleObject( pi.hProcess, INFINITE);
	std::cout << "MIDI successfully parsed!\n";

    std::ifstream f("resources/song_name.txt");
    std::string song;
    if (f.is_open()){
        getline(f, song);
        f.close();
    }
    else{
        std::cout << "Path error: cant find song_name.txt" << std::endl;
    }

    song += ".ogg";
    return song;
}

BGMusic::BGMusic(){
    std::string song = initParser();
    std::string path = "resources/songs/" + song;
    this->is_loaded = 0;
    try{
        if (!this->music.openFromFile(path))
            throw "Music load error: Wrong path";
        this->is_loaded = 1;
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }

}

void BGMusic::play(){
    if (this->is_loaded && this->music.getStatus() != sf::SoundSource::Playing)
        this->music.play();
    else
        this->music.pause();
}

float BGMusic::getOffset(){
    return this->music.getPlayingOffset().asSeconds();
}