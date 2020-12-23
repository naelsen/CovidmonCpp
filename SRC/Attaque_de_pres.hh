#pragma once
#include <string.h>
#include "Image.hh"

class Attaque_de_pres : public Image
{
private:
    int _degats;
    int _animation;
    sf::Uint16 _portee;
    bool _est_lancee;

public:
    Attaque_de_pres();
    Attaque_de_pres(std::string);
    Attaque_de_pres(Attaque_de_pres const &);
    ~Attaque_de_pres();

    int get_degats() const;
    bool get_est_lancee() const;

    void set_degats(int);
    void set_est_lancee(bool);

    void animate();
    void lancement();
};
