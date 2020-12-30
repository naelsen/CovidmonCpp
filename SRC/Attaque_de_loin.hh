#pragma once
#include <string.h>
#include "Entite.hh"

class Attaque_de_loin : public Entite
{
private:
    int _degats;
    sf::Uint16 _portee;
    bool _est_lancee;
    bool _just_clicked;
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();

public:
    Attaque_de_loin();
    Attaque_de_loin(std::string, std::string);
    Attaque_de_loin(Attaque_de_loin const &);
    ~Attaque_de_loin();

    int get_degats() const;
    sf::Uint16 get_portee() const;
    bool get_est_lancee() const;
    bool get_just_clicked() const;

    void set_degats(int);
    void set_est_lancee(bool);
    void set_just_clicked(bool);

    void move();
    void animate();
    void got_a_clic(sf::RenderWindow &);
};
