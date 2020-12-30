#include "Attaque_de_loin.hh"

Attaque_de_loin::Attaque_de_loin(std::string im, std::string nom) : Entite(im, nom),
                                                                    _degats(16),
                                                                    _est_lancee(false),
                                                                    _just_clicked(true)
{
    this->_speed = 10;
    this->_direction = Up;
}
Attaque_de_loin::Attaque_de_loin()
{
}

Attaque_de_loin::Attaque_de_loin(Attaque_de_loin const &at) : Entite(at),
                                                              _degats(at._degats),
                                                              _est_lancee(at._est_lancee),
                                                              _just_clicked(true)
{
    // std::cout << "charge !\n";
    this->_speed = at._speed;
    this->_direction = at._direction;
    this->_nom = at._nom;
}

Attaque_de_loin::~Attaque_de_loin()
{
}

int Attaque_de_loin::get_degats() const
{
    return this->_degats;
}

bool Attaque_de_loin::get_est_lancee() const
{
    return this->_est_lancee;
}

bool Attaque_de_loin::get_just_clicked() const
{
    return this->_just_clicked;
}

void Attaque_de_loin::set_degats(int d)
{
    this->_degats = d;
}

void Attaque_de_loin::set_est_lancee(bool e)
{
    this->_est_lancee = e;
}

void Attaque_de_loin::set_just_clicked(bool click)
{
    this->_just_clicked = click;
}

void Attaque_de_loin::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK * this->_animation,
                                                    SIZE_BLOCK * this->_direction,
                                                    SIZE_BLOCK,
                                                    SIZE_BLOCK));
}

void Attaque_de_loin::move()
{
    /*  std::cout << "moving" << std::endl;
    std::cout << "x : " << __position_x << std::endl;
    std::cout << "y: " << __position_y << std::endl;
    std::cout << "animation " << _animation << std::endl;
    std::cout << "direction: " << _direction << std::endl;*/
    this->animate();
    if (this->_est_lancee)
    {
        switch (this->_direction)
        {
        case Down:
            this->_move_down();
            break;
        case Right:
            this->_move_right();
            break;
        case Up:
            this->_move_up();
            break;
        case Left:
            this->_move_left();
            break;
        default:
            break;
        }
    }
    else
    {
        this->set_position_x(WINDOW_WIDTH);
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
    else
        set_est_lancee(false);
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
    if (this->__position_y < ARENE_END - SIZE_BLOCK)
        this->__position_y += this->_speed;
    else
        set_est_lancee(false);
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
    if (this->__position_x < ARENE_END - SIZE_BLOCK)
        this->__position_x += this->_speed;
    else
        set_est_lancee(false);
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
        this->__position_x -= this->_speed;
    else
        set_est_lancee(false);
}

void Attaque_de_loin::got_a_clic(sf::RenderWindow &W)
{
}