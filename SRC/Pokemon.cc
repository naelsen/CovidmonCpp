#include "Pokemon.hh"

Pokemon::Pokemon(std::string image, std::string nom, Type _type) : Entite(image, nom),
                                                                   _pv(500)
{
    switch (_type)
    {
    case Vol:
        this->_attaque_de_loin = Attaque("Images/Attaques/lance_vent.png", "jaj", loin);
        this->_attaque_de_pres = Attaque("Images/Attaques/explosion_vent.png", "jaj", pres);
        break;
    case Feu:
        this->_attaque_de_loin = Attaque("Images/Attaques/lance_feu.png", "jaj", loin);
        this->_attaque_de_pres = Attaque("Images/Attaques/explosion_feu.png", "jaj", pres);
        break;
    case Eau:
        this->_attaque_de_loin = Attaque("Images/Attaques/lance_eau.png", "jaj", loin);
        this->_attaque_de_pres = Attaque("Images/Attaques/explosion_eau.png", "jaj", pres);
        break;
    case Plante:
        this->_attaque_de_loin = Attaque("Images/Attaques/lance_plante.png", "jaj", loin);
        this->_attaque_de_pres = Attaque("Images/Attaques/explosion_plante.png", "jaj", pres);
        break;
    default:
        break;
    }
}

Pokemon::Pokemon(Pokemon const &pokemon) : Entite(pokemon)
{
    this->_type = pokemon._type;
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
    text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 6));
    window.draw(text);
}

void Pokemon::attaque_de_loin(sf::RenderWindow &window)
{
    if (this->_attaque_de_loin.get_est_lancee())
    {
        this->_attaque_de_loin.draw(window);
        this->_attaque_de_loin.move();
        this->_attaque_de_loin.animate();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        std::cout << "lancement" << std::endl;
        this->_attaque_de_loin.set_position_x(this->get_position_x());
        this->_attaque_de_loin.set_position_y(this->get_position_y());
        this->_attaque_de_loin.set_est_lancee(true);
        this->_attaque_de_loin.set_direction(this->get_direction());
    }
}
void Pokemon::collision_attaque(Pokemon &P)
{
    if (this->_attaque_de_loin.distance(P) < SIZE_BLOCK_POKEMON / 2)
    {
        P.receive_degat(this->_attaque_de_loin.get_degats());
        this->_attaque_de_loin.set_est_lancee(false);
        this->_attaque_de_loin.set_position_x(-SIZE_BLOCK_POKEMON);
        this->_attaque_de_loin.set_position_y(-SIZE_BLOCK_POKEMON);
    }
}

void Pokemon::receive_degat(int degats)

{
    this->_pv -= degats;
}

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