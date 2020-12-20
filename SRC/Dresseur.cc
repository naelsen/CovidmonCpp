#include "Dresseur.hh"

Dresseur::Dresseur(std::string image, std::string nom) : Entite(image, nom)
{
}

Dresseur::Dresseur(Dresseur const &dresseur) : Entite(dresseur)
{
}

Dresseur::~Dresseur()
{
}

void Dresseur::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_WIDTH_PERSO * this->_animation, SIZE_HEIGHT_PERSO * this->_direction, SIZE_WIDTH_PERSO, SIZE_HEIGHT_PERSO));
}

void Dresseur::print_name(sf::RenderWindow &window)
{
    this->_font.loadFromFile("Images/arial.ttf");
    sf::Text text("Joueur 1 : " + this->get_nom(), this->_font);
    text.setCharacterSize(15);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(12, 6));
    window.draw(text);
}

bool Dresseur::is_out()
{
    if (this->__position_x > WINDOW_WIDTH)
        return true;

    return false;
}

void Dresseur::_move_up()
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
    if (this->__position_x < WINDOW_WIDTH - SIZE_WIDTH_PERSO + 1)
    {
        if (this->__position_y > 0)
        {
            this->__position_y -= this->_speed;
            if (this->__position_y < 0)
                this->__position_y = 0;
        }
    }
    else
    {
        this->__position_y -= this->_speed;
        if (this->__position_y < WINDOW_HEIGHT / 2 - 90)
            this->__position_y = WINDOW_HEIGHT / 2 - 90;
    }
}

void Dresseur::_move_down()
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
    if (this->__position_x < WINDOW_WIDTH - SIZE_WIDTH_PERSO + 1)
    {
        if (this->__position_y < WINDOW_HEIGHT - SIZE_HEIGHT_PERSO)
        {
            this->__position_y += this->_speed;
            if (this->__position_y > WINDOW_HEIGHT - SIZE_HEIGHT_PERSO)
                this->__position_y = WINDOW_HEIGHT - SIZE_HEIGHT_PERSO;
        }
    }
    else
    {
        this->__position_y += this->_speed;
        if (this->__position_y > WINDOW_HEIGHT / 2 - 40)
            this->__position_y = WINDOW_HEIGHT / 2 - 40;
    }
}

void Dresseur::_move_right()
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
    if (this->__position_y < WINDOW_HEIGHT / 2 - 90 || this->__position_y > WINDOW_HEIGHT / 2 - 40)
    {
        if (this->__position_x < WINDOW_HEIGHT - SIZE_WIDTH_PERSO)
        {
            this->__position_x += this->_speed;
            if (this->__position_x > WINDOW_HEIGHT - SIZE_WIDTH_PERSO)
                this->__position_x = WINDOW_HEIGHT - SIZE_WIDTH_PERSO;
        }
    }
    else
    {
        this->__position_x += this->_speed;
    }
}

void Dresseur::_move_left()
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
    if (this->__position_x > 0)
    {
        this->__position_x -= this->_speed;
        if (this->__position_x < 0)
            this->__position_x = 0;
    }
}

void Dresseur::got_a_clic(sf::RenderWindow &window)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    sf::Uint16 dx = pos.x - this->__position_x;
    sf::Uint16 dy = pos.y - this->__position_y;
    bool collision_x = dx < SIZE_WIDTH_PERSO;
    bool collision_y = dy < SIZE_HEIGHT_PERSO;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (collision_x && collision_y)
        {
            this->_choisi = true;
        }
        else
            this->_choisi = false;
    }
}