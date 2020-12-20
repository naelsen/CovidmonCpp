#include <string.h>

#include "Image.hh"

class Attaque : public Image
{
private:
    int _degats;
    int _animation;

public:
    Attaque(std::string);
    ~Attaque();

    void set_degats();
};
