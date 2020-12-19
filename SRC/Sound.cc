#include "Sound.hh"

Sound::Sound(std::string fichier)
{
    if (!this->_buffer.loadFromFile(fichier))
		std::cout<<"Erreur chargement son"<<std::endl;

	this->_sound.setBuffer(this->_buffer);
}
Sound::Sound(Sound const& S)
{
    this->_sound = S._sound;
    this->_buffer = S._buffer;
}

void Sound::set_sound(std::string fichier)
{    
    this->_buffer.loadFromFile(fichier);
	this->_sound.setBuffer(this->_buffer);   
}

void Sound::play()
{
    this->_sound.play();
}

Sound::~Sound(){}