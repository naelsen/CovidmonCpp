#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "Image.hh"
#include "define.hh"
class Dresseur: public Image
{
private:
    sf::Clock _clock;
    sf::SoundBuffer _buffer;
    sf::Sound _sound;

    float _speed;    
    Direction _direction;
    int _animation;
    bool _choisi;

    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();
public:
    Dresseur(std::string);
    Dresseur(Dresseur const&);
    ~Dresseur();
    float get_speed() const;
    Direction get_direction() const;
    int get_animation() const;
    bool get_choisi() const;
    void set_speed(float);
    void set_direction(Direction);
    void set_choisi(bool);
    void set_animation(int);
    void _animate();
    void got_a_clic(sf::RenderWindow&);
    void move();
};
