#pragma once
#include "Personnage.hh"

class Dresseur: public Personnage
{
private : 
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();
    
public:
    Dresseur(std::string,std::string);
    Dresseur(Dresseur const&);
    ~Dresseur();

    void animate();
    bool is_out();
};
