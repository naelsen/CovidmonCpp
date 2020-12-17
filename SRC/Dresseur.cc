#include "Dresseur.hh"

Dresseur::Dresseur(std::string image,std::string nom):
Entite(image,nom)
{}

Dresseur::Dresseur(Dresseur const& dresseur):
Entite(dresseur)
{}

Dresseur::~Dresseur()
{}

void Dresseur::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_WIDTH_PERSO*this->_animation,
     SIZE_HEIGHT_PERSO *this->_direction, SIZE_WIDTH_PERSO, SIZE_HEIGHT_PERSO));
}

bool Dresseur::is_out()
{
    sf::Uint16 dx = WINDOW_WIDTH - this->__position_x;
    sf::Uint16 dy = WINDOW_HEIGHT/2 - this->__position_y;

    bool collision_x = dx < SIZE_WIDTH_PERSO;
    bool collision_y = dy < SIZE_WIDTH_PERSO;
    if(collision_x && collision_y)
        return true;

    return false;
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
    if(this->__position_y < WINDOW_HEIGHT - SIZE_HEIGHT_PERSO)
    {
        this->__position_y += this->_speed;
        if(this->__position_y > WINDOW_HEIGHT - SIZE_HEIGHT_PERSO)
            this->__position_y = WINDOW_HEIGHT - SIZE_HEIGHT_PERSO;
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
    if(this->__position_x < WINDOW_HEIGHT - SIZE_WIDTH_PERSO)
    {
        this->__position_x += this->_speed;
        if(this->__position_x> WINDOW_HEIGHT - SIZE_WIDTH_PERSO)
            this->__position_x = WINDOW_HEIGHT - SIZE_WIDTH_PERSO;
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