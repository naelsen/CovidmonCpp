#include "Personnage.hh"

Personnage::Personnage(std::string image,std::string nom):
Image(image),
_nom(nom),
_speed(2),
_direction(Down),
_animation(0),
_choisi(false)
{}

Personnage::Personnage(Personnage const& Personnage):
Image(Personnage),
_nom(Personnage._nom),
_speed(Personnage._speed),
_direction(Personnage._direction),
_animation(Personnage._animation)
{}

Personnage::~Personnage()
{}

std::string Personnage::get_nom() const
{
    return this->_nom;
}

sf::Uint16 Personnage::get_speed() const
{
    return _speed;
}

Direction Personnage::get_direction() const
{
    return _direction;
}

int Personnage::get_animation() const
{
    return _animation;
}

bool Personnage::get_choisi() const
{
    return _choisi;
}

void Personnage::set_nom(std::string nom)
{
    this->_nom = nom; 
}

void Personnage::set_speed(sf::Uint16 speed)
{
    this->_speed = speed;
}

void Personnage::set_direction(Direction direction)
{
    this->_direction = direction;
}

void Personnage::set_choisi(bool choix)
{
    this->_choisi = choix;
}
void Personnage::set_animation(int animation)
{
    this->_animation = animation;
}

void Personnage::got_a_clic(sf::RenderWindow& window)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    sf::Uint16 dx = pos.x - this->__position_x;
	sf::Uint16 dy = pos.y - this->__position_y;
	bool collision_x = dx < SIZE_WIDTH_PERSO;
	bool collision_y = dy < SIZE_WIDTH_PERSO;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(collision_x && collision_y)
        {
            _choisi = true;
        }
        else
            _choisi = false;
    }

}

void Personnage::move()
{
    if(this->_clock.getElapsedTime().asSeconds() > 0.30f)
        this->_animation=0;
    this->animate();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _move_up();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _move_down();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _move_right();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _move_left();
}