#pragma once

#include <SFML/Graphics.hpp>

#include "Entite.hh"

class Dresseur: public Entite
{
private : 
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();
    sf::Font _font;
public:
    Dresseur(std::string,std::string);
    Dresseur(Dresseur const&);
    ~Dresseur();

    void animate();
    bool is_out();
    void got_a_clic(sf::RenderWindow&);
    void print_name(sf::RenderWindow&);
};
