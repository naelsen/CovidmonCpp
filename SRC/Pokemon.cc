#include "Pokemon.hh"

Pokemon::Pokemon(std::string image,std::string nom):
Entite(image,nom)
{}

Pokemon::Pokemon(Pokemon const& pokemon):
Entite::Entite(pokemon)
{}

Pokemon::~Pokemon()
{}

void Pokemon::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK_POKEMON*this->_animation,
     SIZE_BLOCK_POKEMON *this->_direction,SIZE_BLOCK_POKEMON,SIZE_BLOCK_POKEMON));
}

void Pokemon::_move_up()
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

void Pokemon::_move_down()
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
    if(this->__position_y < WINDOW_HEIGHT - SIZE_BLOCK_POKEMON)
    {
        this->__position_y += this->_speed;
        if(this->__position_y > WINDOW_HEIGHT - SIZE_BLOCK_POKEMON)
            this->__position_y = WINDOW_HEIGHT - SIZE_BLOCK_POKEMON;
    }
}

void Pokemon::_move_right()
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
    if(this->__position_x < WINDOW_HEIGHT - SIZE_BLOCK_POKEMON)
    {
        this->__position_x += this->_speed;
        if(this->__position_x> WINDOW_HEIGHT - SIZE_BLOCK_POKEMON)
            this->__position_x = WINDOW_HEIGHT - SIZE_BLOCK_POKEMON;
    }
}

void Pokemon::_move_left()
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