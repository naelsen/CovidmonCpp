#pragma once

#include "Personnage.hh"

class Pokemon : public Personnage
{
private : 
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();
    // Attaque* Att_cac;
    // Attaque* Att_dist;
    
public:
    Pokemon(std::string,std::string);
    Pokemon(Pokemon const&);
    ~Pokemon();

    void animate();
    //void attaque()
};