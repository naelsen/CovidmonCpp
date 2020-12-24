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
	sf::Texture __texture_pv;
	sf::Sprite __sprite_pv;

    Type _type;
    Attaque_de_loin  _attaque_de_loin;
    Attaque_de_pres  _attaque_de_pres;
    sf::Uint16 _pv;
    bool _est_vivant;
    
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();

public:
    Covidmon();
    Covidmon(std::string, std::string,Type);
    Covidmon(Covidmon const &);
    ~Covidmon();

    Type get_type();
    sf::Uint16 get_pv();
    bool get_est_vivant();
    Attaque_de_loin get_attaque_de_loin();
    Attaque_de_pres get_attaque_de_pres();
    void set_type(Type t);
    void set_pv(sf::Uint16);
    void set_est_vivant(bool);
    void animate();
    void attaque_de_loin(sf::RenderWindow&);
    void attaque_de_pres(sf::RenderWindow&);
    void collision_attaque(Covidmon&);
    bool est_fort_contre(Covidmon&);
    bool est_faible_contre(Covidmon&);
    void receive_degat(Covidmon&);
    void got_a_clic(sf::RenderWindow &);
    void print_name(sf::RenderWindow &);
    void print_pv(sf::RenderWindow &);
    void draw_pv(sf::RenderWindow &);
};