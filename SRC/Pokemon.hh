#pragma once

#include "Entite.hh"
#include "Attaque.hh"

typedef enum Type
{
    Feu,
    Eau,
    Plante,
    Vol
} Type;

class Pokemon : public Entite
{
private:
    sf::Font _font;
    Type _type;
    Attaque _attaque_de_loin;
    Attaque _attaque_de_pres;
    int _pv;

    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();
    // Attaque* Att_cac;
    // Attaque* Att_dist;

public:
    Pokemon(std::string, std::string, Type);
    Pokemon(Pokemon const &);
    ~Pokemon();

    Type get_type();
    int get_pv();
    void set_type(Type t);
    void animate();
    void attaque_de_loin(sf::RenderWindow &);
    //void attaque_de_pres(sf::RenderWindow&);
    void collision_attaque(Pokemon &p);
    void receive_degat(int);
    void got_a_clic(sf::RenderWindow &);
    void print_name(sf::RenderWindow &);
    //void attaque()
};