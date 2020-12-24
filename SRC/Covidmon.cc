#include "Covidmon.hh"

Covidmon::Covidmon()
{
}

Covidmon::Covidmon(std::string image, std::string nom, Type _type) : Entite(image, nom),
                                                                     _type(_type),
                                                                     _est_vivant(true)
{

    if(_type == Vol)
    {
        this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_vent.png", "jaj");
        this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_vent.png");
        this->_pv_max = 500;
        this->_pv_current = 500;
        this->_speed = 4;
    }
    else if(_type == Feu)
    {
        this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_feu.png", "jaj");
        this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_feu.png");
        this->_pv_max = 650;
        this->_pv_current = 650;
        this->_speed = 3;
    }
    else if(_type == Eau)
    {
        this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_eau.png", "jaj");
        this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_eau.png");
        this->_pv_max = 800;
        this->_pv_current = 800;
        this->_speed = 3;
    }
    else if(_type == Plante)
    {
        this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_plante.png", "jaj");
        this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_plante.png");
        this->_pv_max = 800;
        this->_pv_current = 800;
        this->_speed = 3;
    }
    this->_font.loadFromFile("Images/arial.ttf");
    if(!__texture_pv.loadFromFile("Images/vie2.png")) {std::cout << "Erreur chargement de vie" << std::endl;}
    this->__sprite_pv.setTexture(this->__texture_pv);
    this->__sprite_pv.setScale(sf::Vector2f(0.08f,0.12f));
}

Covidmon::Covidmon(Covidmon const &Covidmon) : Entite(Covidmon),
                                               _type(Covidmon._type),
                                               _attaque_de_loin(Covidmon._attaque_de_loin),
                                               _attaque_de_pres(Covidmon._attaque_de_pres),
                                               _pv_current(Covidmon._pv_current),
                                               _pv_max(Covidmon._pv_max)
{
    this->_nom = Covidmon._nom;
    this->_font.loadFromFile("Images/arial.ttf");
    if(!__texture_pv.loadFromFile("Images/vie2.png")) {std::cout << "Erreur chargement de vie" << std::endl;}
    this->__sprite_pv.setTexture(this->__texture_pv);
    this->__sprite_pv.setScale(sf::Vector2f(0.08f,0.12f));
}

Covidmon::~Covidmon()
{
}

Type Covidmon::get_type() { return this->_type; }

void Covidmon::set_type(Type t) { this->_type = t; }

sf::Uint16 Covidmon::get_pv_max() { return this->_pv_max; }

sf::Uint16 Covidmon::get_pv_current() { return this->_pv_current; }

void Covidmon::set_pv_max(sf::Uint16 pv) { this->_pv_max = pv; }

void Covidmon::set_pv_current(sf::Uint16 pv) { this->_pv_current = pv; }

bool Covidmon::get_est_vivant(){ return this->_est_vivant; }

void Covidmon::set_est_vivant(bool v){ this->_est_vivant = v; }

Attaque_de_loin Covidmon::get_attaque_de_loin() { return this->_attaque_de_loin; }

Attaque_de_pres Covidmon::get_attaque_de_pres() { return this->_attaque_de_pres; }

void Covidmon::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK * this->_animation,
                                                    SIZE_BLOCK * this->_direction,
                                                    SIZE_BLOCK,
                                                    SIZE_BLOCK));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if(this->_pv_current >0)
            this->_pv_current -= 1;
        else 
        {
            this->_pv_current = 0;
            this->set_est_vivant(false);
            set_position_x(-100);
        }
    }
}

void Covidmon::print_name(sf::RenderWindow &window)
{
    sf::Text text("Covidmon choisi : " + this->get_nom(), _font);
    text.setCharacterSize(15);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 6));
    window.draw(text);
}

void Covidmon::draw_pv(sf::RenderWindow &window)
{
    int bar;

    if(100*this->get_pv_current() / this->get_pv_max() >= 100){ bar = 0;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 92) { bar = 1;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 85) { bar = 2;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 78) { bar = 3;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 71) { bar = 4;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 64) { bar = 5;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 57) { bar = 6;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 42) { bar = 7;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 35) { bar = 8;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 28) { bar = 9;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 21) { bar = 10;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 14) { bar = 11;}
    else if(100*this->get_pv_current() / this->get_pv_max() >= 7)  { bar = 12;}
    else                                                           { bar = 13;}

    this->__sprite_pv.setTextureRect(sf::IntRect(0,
                                                 bar*LARGEUR_VIE,
                                                 LONGUEUR_VIE,
                                                 LARGEUR_VIE));
    this->__sprite_pv.setPosition(this->get_position_x(),this->get_position_y()- SIZE_BLOCK/4);
    //std::cout << 100*this->get_pv_current() / this->get_pv_max();
    int percent_pv = 100*this->get_pv_current() / this->get_pv_max();
    sf::Text text(std::to_string(percent_pv)+"%", _font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(this->get_position_x()+SIZE_BLOCK/3, this->get_position_y()- SIZE_BLOCK/2));
    window.draw(text);
    window.draw(this->__sprite_pv);
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
    if (this->_attaque_de_loin.distance(P) < SIZE_BLOCK / 3)
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
        //this->_attaque_de_pres.set_position_x(-SIZE_BLOCK);
        //this->_attaque_de_pres.set_position_y(-SIZE_BLOCK);
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
    if (this->get_pv_current()>30000)
        this->set_pv_current(0);
    if (this->est_faible_contre(P))
    {
        if(this->_attaque_de_loin.get_est_lancee())
            P.set_pv_current(get_pv_current() - 0.75 * this->_attaque_de_loin.get_degats());
        if(this->_attaque_de_pres.get_est_lancee())
            P.set_pv_current(get_pv_current() - 0.75 * this->_attaque_de_pres.get_degats());
    }
    else if (this->est_fort_contre(P))
    {
        if(this->_attaque_de_loin.get_est_lancee())
            P.set_pv_current(get_pv_current() - 1.25 * this->_attaque_de_loin.get_degats());
        if(this->_attaque_de_pres.get_est_lancee())
            P.set_pv_current(get_pv_current() - 1.25 * this->_attaque_de_pres.get_degats());
    }
    else
    {
        if(this->_attaque_de_loin.get_est_lancee())
            P.set_pv_current(get_pv_current() - this->_attaque_de_loin.get_degats());
        if(this->_attaque_de_pres.get_est_lancee())
            P.set_pv_current(get_pv_current() - this->_attaque_de_pres.get_degats());
    }

    if(P.get_pv_current() == 0){
        P.set_est_vivant(false);
    }
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