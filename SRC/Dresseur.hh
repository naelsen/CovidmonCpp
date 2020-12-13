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
    std::string _nom;

    sf::Uint16 _speed;    
    Direction _direction;
    int _animation;
    bool _choisi;

    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();
public:
    Dresseur(std::string,std::string);
    Dresseur(Dresseur const&);
    ~Dresseur();
    std::string get_nom() const;
    sf::Uint16 get_speed() const;
    Direction get_direction() const;
    int get_animation() const;
    bool get_choisi() const;
    void set_nom(std::string);
    void set_speed(sf::Uint16);
    void set_direction(Direction);
    void set_choisi(bool);
    void set_animation(int);
    void _animate();
    void got_a_clic(sf::RenderWindow&);
    bool is_out();

    void move();
};
