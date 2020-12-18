#include "Attaque.hh"

Attaque::Attaque(std::string im):
Image(im),
_degats(10),
_animation(0)
{}

Attaque::~Attaque()
{
}
