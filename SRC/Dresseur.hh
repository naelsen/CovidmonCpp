#pragma once
#include "Entite.hh"

class Dresseur: public Entite
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
