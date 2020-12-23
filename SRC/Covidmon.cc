#include "Covidmon.hh"

Covidmon::Covidmon()
{
}

Covidmon::Covidmon(std::string image, std::string nom, Type _type) : Entite(image, nom),
                                                                     _type(_type),
                                                                     _pv(500)
{

    if(_type == Vol)
    {
        this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_vent.png", "jaj");
        this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_vent.png");
    }
    else if(_type == Feu)
    {
        this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_feu.png", "jaj");
        this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_feu.png");
    }
    else if(_type == Eau)
    {
        this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_eau.png", "jaj");
        this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_eau.png");
    }
    else if(_type == Plante)
    {
        this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_plante.png", "jaj");
        this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_plante.png");
    }
}

Covidmon::Covidmon(Covidmon const &Covidmon) : Entite(Covidmon),
                                               _type(Covidmon._type),
                                               _attaque_de_loin(Covidmon._attaque_de_loin),
                                               _attaque_de_pres(Covidmon._attaque_de_pres),
                                               _pv(Covidmon._pv)

{
    this->_nom = Covidmon._nom;
}

Covidmon::~Covidmon()
{
}

Type Covidmon::get_type() { return this->_type; }

void Covidmon::set_type(Type t) { this->_type = t; }

int Covidmon::get_pv() { return this->_pv; }

void Covidmon::set_pv(int pv) { this->_pv = pv; }

void Covidmon::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK * this->_animation,
                                                    SIZE_BLOCK * this->_direction,
                                                    SIZE_BLOCK,
                                                    SIZE_BLOCK));
}

void Covidmon::print_name(sf::RenderWindow &window)
{
    this->_font.loadFromFile("Images/arial.ttf");
    sf::Text text("Covidmon choisi : " + this->get_nom(), _font);
    text.setCharacterSize(15);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 6));
    window.draw(text);
}

void Covidmon::attaque_de_loin(sf::RenderWindow &window)
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
        this->_attaque_de_loin.set_direction(this->get_direction());
        this->_attaque_de_loin.set_est_lancee(true);
    }
}

void Covidmon::attaque_de_pres(sf::RenderWindow &window)
{
    if (this->_attaque_de_pres.get_est_lancee())
    {
        this->_attaque_de_pres.lancement();
        this->_attaque_de_pres.draw(window);
        this->_attaque_de_pres.animate();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        switch(this->_direction)
        {
        case Up:
            this->_attaque_de_pres.set_position_x(this->get_position_x());
            this->_attaque_de_pres.set_position_y(this->get_position_y() - SIZE_BLOCK/2);
            break;
        case Down:
            this->_attaque_de_pres.set_position_x(this->get_position_x());
            this->_attaque_de_pres.set_position_y(this->get_position_y() + SIZE_BLOCK/2);
            break;
        case Right:
            this->_attaque_de_pres.set_position_x(this->get_position_x() + SIZE_BLOCK/2);
            this->_attaque_de_pres.set_position_y(this->get_position_y());
            break;
        case Left:
            this->_attaque_de_pres.set_position_x(this->get_position_x() - SIZE_BLOCK/2);
            this->_attaque_de_pres.set_position_y(this->get_position_y());
            break;
        }
    this->_attaque_de_pres.set_est_lancee(true);
    }
}

void Covidmon::collision_attaque(Covidmon &P)
{
    if (this->_attaque_de_loin.distance(P) < SIZE_BLOCK / 2)
    {
        this->receive_degat(P);
        this->_attaque_de_loin.set_est_lancee(false);
        this->_attaque_de_loin.set_position_x(-SIZE_BLOCK);
        this->_attaque_de_loin.set_position_y(-SIZE_BLOCK);
    }
    if (this->_attaque_de_pres.distance(P) < SIZE_BLOCK / 2)
    {
        this->receive_degat(P);
        this->_attaque_de_pres.set_est_lancee(false);
        this->_attaque_de_pres.set_position_x(-SIZE_BLOCK);
        this->_attaque_de_pres.set_position_y(-SIZE_BLOCK);
    }
}

bool Covidmon::est_faible_contre(Covidmon &P)
{
    switch (this->_type)
    {
    case Eau:
        if (P.get_type() == Plante || P.get_type() == Vol)
            return true;
        break;
    case Feu:
        if (P.get_type() == Eau)
            return true;
        break;
    case Plante:
        if (P.get_type() == Feu || P.get_type() == Vol)
            return true;
        break;
    case Vol:
        return false;
        break;
    default:
        break;
    }
    return false;
}

bool Covidmon::est_fort_contre(Covidmon &P)
{
    switch (this->_type)
    {
    case Eau:
        if (P.get_type() == Feu)
            return true;
        break;
    case Feu:
        if (P.get_type() == Plante)
            return true;
        break;
    case Plante:
        if (P.get_type() == Eau)
            return true;
        break;
    case Vol:
        if (P.get_type() == Eau || P.get_type() == Plante)
            return true;
        break;
    default:
        break;
    }
    return false;
}

void Covidmon::receive_degat(Covidmon &P)
{
    if (this->est_faible_contre(P))
        P.set_pv(get_pv() - 0.5 * this->_attaque_de_loin.get_degats());

    else if (this->est_fort_contre(P))
        P.set_pv(get_pv() - 1.5 * this->_attaque_de_loin.get_degats());
    else
        P.set_pv(get_pv() - this->_attaque_de_loin.get_degats());
}

void Covidmon::_move_up()
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

void Covidmon::_move_down()
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
}

void Covidmon::_move_right()
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
}

void Covidmon::_move_left()
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
}

void Covidmon::got_a_clic(sf::RenderWindow &window)
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
            _choisi = true;
        }
        else
            _choisi = false;
    }
}