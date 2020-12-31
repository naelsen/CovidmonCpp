#pragma once
#include <string.h>
#include "Image.hh"

/* Herite d'image et non d'entité 
 * on ne gere pas de déplacement */
class Attaque_de_pres : public Image
{
private:
    int _degats;
    sf::Uint16 _animation;
    sf::Clock _clock;
    bool _est_lancee;
    bool _just_clicked;

public:
    //Constructeurs / Destructeurs
    Attaque_de_pres();
    Attaque_de_pres(std::string);
    Attaque_de_pres(Attaque_de_pres const &);
    ~Attaque_de_pres();
    //GETTEUR
    int get_degats() const;
    bool get_est_lancee() const;
    bool get_just_clicked() const;
    sf::Uint16 get_animation() const;
    //SETTEUR
    void set_degats(int);
    void set_est_lancee(bool);
    void set_just_clicked(bool);
    void set_animation(sf::Uint16);

    void animate();
    void lancement();
};
