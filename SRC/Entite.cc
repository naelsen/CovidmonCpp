#include "Entite.hh"

Entite::Entite(std::string image, std::string nom) : Image(image),
                                                     _nom(nom),
                                                     _speed(2),
                                                     _direction(Down),
                                                     _animation(0),
                                                     _choisi(false),
                                                     _current_bg(choix_personnage)
{
}

Entite::Entite(Entite const &Entite) : Image(Entite),
                                       _nom(Entite._nom),
                                       _speed(Entite._speed),
                                       _direction(Entite._direction),
                                       _animation(Entite._animation),
                                       _choisi(false),
                                       _current_bg(choix_personnage)
{
}

Entite::Entite()
{
}

Entite::~Entite()
{
}

std::string Entite::get_nom() const
{
    return this->_nom;
}

sf::Uint16 Entite::get_speed() const
{
    return this->_speed;
}

Direction Entite::get_direction() const
{
    return this->_direction;
}

sf::Uint16 Entite::get_animation() const
{
    return this->_animation;
}

bool Entite::get_choisi() const
{
    return this->_choisi;
}

Bg Entite::get_current_bg() const
{
    return this->_current_bg;
}

void Entite::set_nom(std::string nom)
{
    this->_nom = nom;
}

void Entite::set_speed(sf::Uint16 speed)
{
    this->_speed = speed;
}

void Entite::set_direction(Direction direction)
{
    this->_direction = direction;
}

void Entite::set_choisi(bool choix)
{
    this->_choisi = choix;
}

void Entite::set_current_bg(Bg bg)
{
    this->_current_bg = bg;
}

void Entite::set_animation(sf::Uint16 animation)
{
    this->_animation = animation;
}

void Entite::move()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.30f)
        this->_animation = 0;
    this->animate();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->_move_up();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->_move_down();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->_move_right();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->_move_left();
}
