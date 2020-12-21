#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "define.hh"
#include "Image.hh"

class Entite : public Image
{
protected:
    sf::Clock _clock;
    std::string _nom;
    sf::Uint16 _speed;

    Direction _direction;
    sf::Uint16 _animation;
    bool _choisi;

    virtual void _move_up() = 0;
    virtual void _move_down() = 0;
    virtual void _move_right() = 0;
    virtual void _move_left() = 0;

public:
    Entite(std::string, std::string);
    Entite(Entite const &);
    ~Entite();
    std::string get_nom() const;
    sf::Uint16 get_speed() const;
    Direction get_direction() const;
    sf::Uint16 get_animation() const;
    bool get_choisi() const;
    void set_nom(std::string);
    void set_speed(sf::Uint16);
    void set_direction(Direction);
    void set_choisi(bool);
    void set_animation(sf::Uint16);
    virtual void animate() = 0;
    virtual void got_a_clic(sf::RenderWindow &) = 0;
    void move();
};