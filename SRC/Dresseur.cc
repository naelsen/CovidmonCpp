#include "Dresseur.hh"

Dresseur::Dresseur(std::string image, std::string nom) : Entite(image, nom)
{
    this->_font.loadFromFile("Images/arial.ttf");
    this->_text.setFont(this->_font);
    this->_text.setString("Joueur 1 : " + this->get_nom());
    this->_text.setCharacterSize(15);
    this->_text.setStyle(sf::Text::Bold);
    this->_text.setFillColor(sf::Color::Red);
    this->_text.setPosition(sf::Vector2f(12, 6));
}

Dresseur::Dresseur(Dresseur const &dresseur) : Entite(dresseur)
{
    this->_font.loadFromFile("Images/arial.ttf");
    this->_text.setFont(this->_font);
    this->_text.setString("Joueur 1 : " + this->get_nom());
    this->_text.setCharacterSize(15);
    this->_text.setStyle(sf::Text::Bold);
    this->_text.setFillColor(sf::Color::Red);
    this->_text.setPosition(sf::Vector2f(12, 6));
}

Dresseur::~Dresseur()
{
}

void Dresseur::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK * this->_animation, SIZE_BLOCK * this->_direction, SIZE_BLOCK, SIZE_BLOCK));
}

bool Dresseur::is_out()
{
    if (this->__position_x > WINDOW_WIDTH && this->__position_x < 2 * WINDOW_WIDTH)
        return true;

    return false;
}

void Dresseur::got_a_clic(sf::RenderWindow &window)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    sf::Uint16 dx = pos.x - this->__position_x;
    sf::Uint16 dy = pos.y - this->__position_y;
    bool collision_x = dx < SIZE_BLOCK;
    bool collision_y = dy < SIZE_BLOCK;
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

void Dresseur::print_name(sf::RenderWindow &window)
{
    window.draw(this->_text);
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
    if (this->__position_x < WINDOW_WIDTH - SIZE_BLOCK + 1)
    {
        if (this->__position_y > 0 && this->__position_y < 65000)
            this->__position_y -= this->_speed;
        else
            this->__position_y = 0;
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
    if (this->__position_x < WINDOW_WIDTH - SIZE_BLOCK + 1)
    {
        if (this->__position_y < WINDOW_HEIGHT - SIZE_BLOCK)
            this->__position_y += this->_speed;
        else
            this->__position_y = WINDOW_HEIGHT - SIZE_BLOCK;
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
        if (this->__position_x < WINDOW_HEIGHT - SIZE_BLOCK)
        {
            this->__position_x += this->_speed;
            if (this->__position_x > WINDOW_HEIGHT - SIZE_BLOCK)
                this->__position_x = WINDOW_HEIGHT - SIZE_BLOCK;
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
    if (this->__position_x > 0 && this->__position_x < 65000)
    {
        this->__position_x -= this->_speed;
    }
    else
        this->__position_x = 0;
}