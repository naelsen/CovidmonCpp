#pragma once
#include <string.h>
#include "Image.hh"

class Attaque_de_pres : public Image
{
private:
    int _degats;
    sf::Uint16 _animation;
    sf::Uint16 _portee;
    sf::Clock _clock;
    bool _est_lancee;

public:
    Attaque_de_pres();
    Attaque_de_pres(std::string);
    Attaque_de_pres(Attaque_de_pres const &);
    ~Attaque_de_pres();

    int get_degats() const;
    bool get_est_lancee() const;
    sf::Uint16 get_animation() const;

    void set_degats(int);
    void set_est_lancee(bool);
    void set_animation(sf::Uint16);

    void animate();
    void lancement();
};
