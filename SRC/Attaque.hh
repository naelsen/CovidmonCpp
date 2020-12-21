#include <string.h>

#include "Entite.hh"

typedef enum Range{
    loin,
    pres
}Range;

class Attaque : public Entite
{
private:
    int _degats;
    sf::Uint16 _portee;
    Range _range;
    float _mult;
    bool _est_lancee;
    void _move_up();
    void _move_down();
    void _move_right();
    void _move_left();

public:
    Attaque();
    Attaque(std::string,std::string ,Range);
    Attaque(Attaque const&);
    ~Attaque();

    int get_degats();
    sf::Uint16 get_portee();
    Range get_range();
    float get_mult();
    bool get_est_lancee();

    void set_degats(int);
    void set_range(Range);
    void set_mult(float);
    void set_est_lancee(bool);

    void move();
    void animate();
    void got_a_clic(sf::RenderWindow&);
};
