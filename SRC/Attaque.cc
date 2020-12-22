#include "Attaque.hh"

Attaque::Attaque(std::string im, std::string nom, Range R) : Entite(im, nom),
                                                             _degats(50),
                                                             _range(R)
{
    this->_speed = 3;
    this->_direction = Up;
    this->_portee = 400;
}

Attaque::Attaque() : _degats(50),
                     _portee(400)
{
    this->_direction = Up;
}

Attaque::Attaque(Attaque const &at) : Entite(at),
                                      _degats(at._degats)
{
}

Attaque::~Attaque()
{
}

int Attaque::get_degats() { return this->_degats; }

sf::Uint16 Attaque::get_portee() { return this->_portee; }

Range Attaque::get_range() { return this->_range; }

float Attaque::get_mult() { return this->_mult; }

bool Attaque::get_est_lancee() { return this->_est_lancee; }

void Attaque::set_degats(int d) { this->_degats = d; }

void Attaque::set_range(Range R) { this->_range = R; }

void Attaque::set_mult(float m) { this->_mult = m; }

void Attaque::set_est_lancee(bool e) { this->_est_lancee = e; }

void Attaque::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK_POKEMON * this->_animation,
                                                    SIZE_BLOCK_POKEMON * this->_direction,
                                                    SIZE_BLOCK_POKEMON,
                                                    SIZE_BLOCK_POKEMON));
}

void Attaque::move()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.30f)
        this->_animation = 0;
    this->animate();
    if (this->_est_lancee)
    {
        switch (this->_direction)
        {
        case Up:
            this->_move_up();
            break;
        case Right:
            this->_move_right();
            break;
        case Left:
            this->_move_left();
            break;
        case Down:
            this->_move_down();
            break;
        default:
            break;
        }
    }
}

void Attaque::_move_up()
{
    sf::Uint16 dist = this->_portee;
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Up;
    if (this->__position_y > ARENE_START && dist > 0)
    {
        this->__position_y -= this->_speed;
        dist -= this->_speed;
        if (this->__position_y < 0)
            this->__position_y = 0;
    }
    else
        this->set_est_lancee(false);
}

void Attaque::_move_down()
{
    sf::Uint16 dist = this->_portee;
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Down;
    if (this->__position_y < ARENE_END && dist > 0)
    {
        this->__position_y += this->_speed;
        dist -= this->_speed;
        if (this->__position_y > WINDOW_HEIGHT)
            this->__position_y = WINDOW_HEIGHT;
    }
    else
        this->set_est_lancee(false);
}

void Attaque::_move_right()
{
    sf::Uint16 dist = this->_portee;
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Right;
    if (this->__position_x < ARENE_END && dist > 0)
    {
        this->__position_x += this->_speed;
        dist -= this->_speed;
        if (this->__position_x > WINDOW_HEIGHT)
            this->__position_x = WINDOW_HEIGHT;
    }
    else
        this->set_est_lancee(false);
}

void Attaque::_move_left()
{
    sf::Uint16 dist = this->_portee;
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
    }
    this->_direction = Left;
    if (this->__position_x > ARENE_START && dist > 0)
    {
        this->__position_x -= this->_speed;
        dist -= this->_speed;
        if (this->__position_x < 0)
            this->__position_x = 0;
    }
    else
        this->set_est_lancee(false);
}

void Attaque::got_a_clic(sf::RenderWindow &W)
{
}