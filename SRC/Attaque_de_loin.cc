#include "Attaque_de_loin.hh"

Attaque_de_loin::Attaque_de_loin(std::string im, std::string nom) :
Entite(im,nom),
_degats(50)
{
    this->_speed = 3;
    this->_direction = Up;
    this->_portee = 400;
}
Attaque_de_loin::Attaque_de_loin(): 
_degats(50),
_portee(400)
{
    this->_direction = Up;
}

Attaque_de_loin::Attaque_de_loin(Attaque_de_loin const& at) : Entite (at),
_degats(at._degats)
{
}

Attaque_de_loin::~Attaque_de_loin()
{
}

int Attaque_de_loin::get_degats(){return this->_degats;}

sf::Uint16 Attaque_de_loin::get_portee(){return this->_portee;}

bool Attaque_de_loin::get_est_lancee(){return this->_est_lancee;}

void Attaque_de_loin::set_degats(int d){this->_degats = d;}


void Attaque_de_loin::set_est_lancee(bool e){this->_est_lancee = e;}

void Attaque_de_loin::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK*this->_animation,
                                                    SIZE_BLOCK*this->_direction,
                                                    SIZE_BLOCK,
                                                    SIZE_BLOCK));
}

void Attaque_de_loin::move()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.30f)
        this->_animation = 0;
    this->animate();
    if (this->_est_lancee)
    {
        switch(this->_direction)
        {
            case Up: this->_move_down(); break;
            case Right: this->_move_right(); break;
            case Left: this->_move_up(); break;
            case Down: this->_move_left(); break;
            default: break;
        }
    }
}

void Attaque_de_loin::_move_up()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Up;
    if (this->__position_y > ARENE_START)
        this->__position_y -= this->_speed;
}

void Attaque_de_loin::_move_down()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Down;
    if (this->__position_y < ARENE_END)
    {
        this->__position_y += this->_speed;
        if (this->__position_y > WINDOW_HEIGHT)
            this->__position_y = WINDOW_HEIGHT;
    }
}

void Attaque_de_loin::_move_right()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Right;
    if (this->__position_x < ARENE_END)
        this->__position_x += this->_speed;
}

void Attaque_de_loin::_move_left()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Left;
    if (this->__position_x > ARENE_START)
    {
        this->__position_x -= this->_speed;
        if (this->__position_x < 0)
            this->__position_x = 0;
    }
}


void Attaque_de_loin::got_a_clic(sf::RenderWindow& W)
{
}