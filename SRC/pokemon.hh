#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Image.hh"
#include "Dresseur.hh"
#include "define.hh"
#include "attaque.hh"

class Pokemon : public Image 
{
private:

    float _speed;    
    Direction _direction;
    int _animation;
    Dresseur *maître;
    std::std::vector<Attaque> _att;

    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();

public:
	Pokemon(std::string);
	Pokemon(const Pokemon &P);
	~Pokemon();

	float get_speed() const;
    Direction get_direction() const;
    int get_animation() const;
    void set_speed(float);
    void set_direction(Direction);
    void set_animation(int);
    void _animate();
	virtual float multiplicator(const Pokemon &P) = 0;
};