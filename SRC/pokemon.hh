#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "Image.hh"
#include "define.hh"
//#include "attaque.hh"

class Pokemon : public Image 
{
private:
    sf::Clock _clock;
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
    std::string _nom;

    float _speed;    
    Direction _direction;
    int _animation;
    //std::std::vector<Attaque> _att;

public:
    Pokemon(std::string image,std::string nom);
	Pokemon(const Pokemon &P);
	~Pokemon();

    Direction get_direction() const;
    int get_animation() const;
    void set_direction(Direction);
    void set_animation(int);
    void _animate();
    void set_nom(std::string nom);
    std::string _get_nom();
};