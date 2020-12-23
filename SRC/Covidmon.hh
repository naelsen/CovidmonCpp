#pragma once

#include "Entite.hh"
#include "Attaque_de_loin.hh"
#include "Attaque_de_pres.hh"

typedef enum Type{
    Feu,
    Eau,
    Plante,
    Vol
}Type;

class Covidmon : public Entite
{
private:
    sf::Font _font;
    Type _type;
    Attaque_de_loin  _attaque_de_loin;
    Attaque_de_pres  _attaque_de_pres;
    int _pv;
    
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();

public:
    Covidmon(std::string, std::string,Type);
    Covidmon(Covidmon const &);
    ~Covidmon();

    Type get_type();
    int get_pv();
    void set_type(Type t);
    void set_pv(int);
    void animate();
    void attaque_de_loin(sf::RenderWindow&);
    void attaque_de_pres(sf::RenderWindow&);
    void collision_attaque(Covidmon&);
    bool est_fort_contre(Covidmon&);
    bool est_faible_contre(Covidmon&);
    void receive_degat(Covidmon&);
    void got_a_clic(sf::RenderWindow &);
    void print_name(sf::RenderWindow &);
    //void attaque()
};