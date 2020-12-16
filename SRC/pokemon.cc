#include "pokemon.hh"

Pokemon::Pokemon(std::string image,std::string nom):
Image(image),
_nom(nom),
 _speed(0),
 _direction(Down),
 _animation(0)
{}

Pokemon::Pokemon(Pokemon const& pokemon):
Image(pokemon),
_nom(pokemon._nom),
_speed(pokemon._speed),
_direction(pokemon._direction),
_animation(pokemon._animation)
{}

Pokemon::~Pokemon(){}


Direction Pokemon::get_direction() const
{
    return _direction;
}

int Pokemon::get_animation() const
{
    return _animation;
}

void Pokemon::_animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK_POKEMON*this->_animation,
        SIZE_BLOCK_POKEMON *this->_direction, SIZE_BLOCK_POKEMON, SIZE_BLOCK_POKEMON));
}

void Pokemon::set_nom(std::string nom)
{
    this->_nom = nom; 
}


void Pokemon::set_direction(Direction direction)
{
    this->_direction = direction;
}

void Pokemon::set_animation(int animation)
{
    this->_animation = animation;
}
