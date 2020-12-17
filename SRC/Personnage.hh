#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "Image.hh"
#include "define.hh"
class Personnage: public Image
{
protected:
    sf::Clock _clock;
    std::string _nom;

    sf::Uint16 _speed;    
    Direction _direction;
    int _animation;
    bool _choisi;

    virtual void _move_up() = 0;
    virtual void _move_down() = 0;
    virtual void _move_right() = 0;
    virtual void _move_left() = 0;
public:
    Personnage(std::string,std::string);
    Personnage(Personnage const&);
    ~Personnage();
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
    virtual void animate();
    void got_a_clic(sf::RenderWindow&);

    void move();
};