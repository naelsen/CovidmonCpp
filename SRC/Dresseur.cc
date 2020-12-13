#include "Dresseur.hh"

Dresseur::Dresseur(std::string image,std::string nom):
Image(image),
_nom(nom),
 _speed(2),
 _direction(Down),
 _animation(0),
 _choisi(false)
{
    if (!this->_buffer.loadFromFile("Sons/b.wav"))
    {
        std::cout << "Erreur Buffer" << std::endl;
    }
    this->_sound.setBuffer(_buffer);
}

Dresseur::Dresseur(Dresseur const& dresseur):
Image(dresseur),
_nom(dresseur._nom),
_speed(dresseur._speed),
_direction(dresseur._direction),
_animation(dresseur._animation),
_choisi(dresseur._choisi)
{}

Dresseur::~Dresseur()
{}

std::string Dresseur::get_nom() const
{
    return this->_nom;
}

sf::Uint16 Dresseur::get_speed() const
{
    return _speed;
}

Direction Dresseur::get_direction() const
{
    return _direction;
}

int Dresseur::get_animation() const
{
    return _animation;
}

bool Dresseur::get_choisi() const
{
    return _choisi;
}

void Dresseur::set_nom(std::string nom)
{
    this->_nom = nom; 
}

void Dresseur::set_speed(sf::Uint16 speed)
{
    this->_speed = speed;
}

void Dresseur::set_direction(Direction direction)
{
    this->_direction = direction;
}

void Dresseur::set_choisi(bool choix)
{
    this->_choisi = choix;
}
void Dresseur::set_animation(int animation)
{
    this->_animation = animation;
}

void Dresseur::_animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_WIDTH_DRESSEUR*this->_animation, SIZE_HEIGHT_DRESSEUR *this->_direction, SIZE_WIDTH_DRESSEUR, SIZE_HEIGHT_DRESSEUR));
}

void Dresseur::got_a_clic(sf::RenderWindow& window)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    sf::Uint16 dx = pos.x - this->__position_x;
	sf::Uint16 dy = pos.y - this->__position_y;
	bool collision_x = dx < SIZE_WIDTH_DRESSEUR;
	bool collision_y = dy < SIZE_WIDTH_DRESSEUR;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(collision_x && collision_y)
        {
            _choisi = true;
            if (this->_sound.getStatus() != sf::Sound::Playing)
                    this->_sound.play();
        }
        else
            _choisi = false;
    }

}

void Dresseur::move()
{
    if(this->_clock.getElapsedTime().asSeconds() > 0.30f)
        this->_animation=0;
    this->_animate();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _move_up();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _move_down();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _move_right();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _move_left();
}


void Dresseur::_move_up()
{
    if(this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if(this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Up;
    if(this->__position_y > 0)
    {
        this->__position_y -= this->_speed;
        if(this->__position_y<0)
            this->__position_y = 0;
    }
}

void Dresseur::_move_down()
{
    if(this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if(this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Down;
    if(this->__position_y < WINDOW_HEIGHT - SIZE_HEIGHT_DRESSEUR)
    {
        this->__position_y += this->_speed;
        if(this->__position_y > WINDOW_HEIGHT - SIZE_HEIGHT_DRESSEUR)
            this->__position_y = WINDOW_HEIGHT - SIZE_HEIGHT_DRESSEUR;
    }
}

void Dresseur::_move_right()
{
    if(this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if(this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Right;
    if(this->__position_x < WINDOW_HEIGHT - SIZE_WIDTH_DRESSEUR)
    {
        this->__position_x += this->_speed;
        if(this->__position_x> WINDOW_HEIGHT - SIZE_WIDTH_DRESSEUR)
            this->__position_x = WINDOW_HEIGHT - SIZE_WIDTH_DRESSEUR;
    }
}

void Dresseur::_move_left()
{
    if(this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if(this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Left;
    if(this->__position_x > 0)
    {
        this->__position_x -= this->_speed;
        if(this->__position_x<0)
            this->__position_x = 0;
    }
}