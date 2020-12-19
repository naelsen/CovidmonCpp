#pragma once 
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

/*
Classe non utiliséé pour l'instant
*/
class Sound
{
private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
public:	
	void setBuffer(sf::SoundBuffer);
    void set_sound(std::string);
    void play();
    Sound(std::string);
    Sound(Sound const&);
    ~Sound();
};

