#include "Pokemon.hh"

Pokemon::Pokemon(std::string image, std::string nom) : Entite(image, nom)
{
}

Pokemon::Pokemon(Pokemon const &pokemon) : Entite(pokemon)
{
}

Pokemon::~Pokemon()
{
}

void Pokemon::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK_POKEMON * this->_animation,
                                                    SIZE_BLOCK_POKEMON * this->_direction,
                                                    SIZE_BLOCK_POKEMON,
                                                    SIZE_BLOCK_POKEMON));
}

void Pokemon::print_name(sf::RenderWindow &window)
{
    this->_font.loadFromFile("Images/arial.ttf");
    sf::Text text("Pokemon choisi : " + this->get_nom(), _font);
    text.setCharacterSize(15);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(WINDOW_WIDTH - 200, 6));
    window.draw(text);
}

// 30,30 ---  570,30 ---- 570,570 ------ 30, 600
void Pokemon::_move_up()
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
    {
        this->__position_y -= this->_speed;
        if (this->__position_y < 0)
            this->__position_y = 0;
    }
}

void Pokemon::_move_down()
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
    if (this->__position_y < ARENE_END - SIZE_BLOCK_POKEMON)
    {
        this->__position_y += this->_speed;
        if (this->__position_y > WINDOW_HEIGHT - SIZE_BLOCK_POKEMON)
            this->__position_y = WINDOW_HEIGHT - SIZE_BLOCK_POKEMON;
    }
}

void Pokemon::_move_right()
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
    if (this->__position_x < ARENE_END - SIZE_BLOCK_POKEMON)
    {
        this->__position_x += this->_speed;
        if (this->__position_x > WINDOW_HEIGHT - SIZE_BLOCK_POKEMON)
            this->__position_x = WINDOW_HEIGHT - SIZE_BLOCK_POKEMON;
    }
}

void Pokemon::_move_left()
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

void Pokemon::got_a_clic(sf::RenderWindow &window)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    sf::Uint16 dx = pos.x - this->__position_x;
    sf::Uint16 dy = pos.y - this->__position_y;
    bool collision_x = dx < SIZE_BLOCK_POKEMON;
    bool collision_y = dy < SIZE_BLOCK_POKEMON;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (collision_x && collision_y)
        {
            _choisi = true;
        }
        else
            _choisi = false;
    }
}