#include "Covidmon.hh"
/*Constructeur par défaut*/
Covidmon::Covidmon()
{
}
/* Constructeur avec paramètres, les attributs sont
 * initialisés différemment selon le type (3eme argument)
 */
Covidmon::Covidmon(std::string image, std::string nom, Type _type) : Entite(image, nom),
                                                                     _type(_type),
                                                                     _est_vivant(true),
                                                                     _bar(0)
{
    /* Les images des attaques sont choisi selon le type du covidmon
     * pv_ current représente les pv actuels, pv_max le pv de base
     * deux attributs utilisés pour le calcul du %
     * initialisation de la vitesse (différente selon le type)
     */
    switch (_type)
    {
        case  Vol:
        {
            this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_vent.png", "Cru-aile");
            this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_vent.png");
            this->_pv_max = 500;
            this->_pv_current = 500;
            this->_speed = 4;
            break;
        }
        case  Feu:
        {
            this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_feu.png", "Lance flamme");
            this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_feu.png");
            this->_pv_max = 650;
            this->_pv_current = 650;
            this->_speed = 3;
            break;
        }
        case  Eau:
        {
            this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_eau.png", "Canon à eau");
            this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_eau.png");
            this->_pv_max = 800;
            this->_pv_current = 800;
            this->_speed = 3;
            break;
        }
        case  Plante:
        {
            this->_attaque_de_loin = Attaque_de_loin("Images/Attaques/lance_plante.png", "Tranche-herbe");
            this->_attaque_de_pres = Attaque_de_pres("Images/Attaques/explosion_plante.png");
            this->_pv_max = 800;
            this->_pv_current = 800;
            this->_speed = 3;
            break;
        }
        default : break;
    }
    /* Affichage de la barre de vie */

    this->_font.loadFromFile("Images/arial.ttf");
    if (!__texture_pv.loadFromFile("Images/vie2.png"))
    {
        std::cout << "Erreur chargement de vie" << std::endl;
    }
    //Chargement sprite et choix de la taille
    this->__sprite_pv.setTexture(this->__texture_pv);
    this->__sprite_pv.setScale(sf::Vector2f(0.08f, 0.12f));
    //Gestion du temps de pause (entre deux attaques successives)
    sf::Clock c1,c2;
    this->_delai_attaques.push_back(c1);
    this->_delai_attaques.push_back(c2);
    this->_delai_attaques[0].restart();
    this->_delai_attaques[1].restart();
}
/* Constructeur par copie, utilisé 
   dans les vector de la classe Game */

Covidmon::Covidmon(Covidmon const &Covidmon) : Entite(Covidmon),
                                               _type(Covidmon._type),
                                               _attaque_de_loin(Covidmon._attaque_de_loin),
                                               _attaque_de_pres(Covidmon._attaque_de_pres),
                                               _pv_current(Covidmon._pv_current),
                                               _pv_max(Covidmon._pv_max),
                                               _est_vivant(Covidmon._est_vivant),
                                               _bar(Covidmon._bar)
{
    //Gestion du temps de pause (entre deux attaques successives)
    sf::Clock c1,c2;
    this->_delai_attaques.push_back(c1);
    this->_delai_attaques.push_back(c2);
    this->_delai_attaques[0].restart();
    this->_delai_attaques[1].restart();
    this->_nom = Covidmon._nom;
    this->_font.loadFromFile("Images/arial.ttf");
    //Chargement sprite et choix de la taille
    if (!__texture_pv.loadFromFile("Images/vie2.png"))
    {
        std::cout << "Erreur chargement de vie" << std::endl;
    }
    this->__sprite_pv.setTexture(this->__texture_pv);
    this->__sprite_pv.setScale(sf::Vector2f(0.08f, 0.12f));
    // Chargement des fichiers audio pour les attaques
    sf::SoundBuffer b1, b2;
    sf::Sound s1,s2;
    this->_buffer_attaques.push_back(b1);
    this->_buffer_attaques.push_back(b2);
    this->_son_attaques.push_back(s1);
    this->_son_attaques.push_back(s2);
    //Charhement des fichiers dans les buffers
    if(!this->_buffer_attaques[0].loadFromFile("Sons/explosion.wav")){std::cerr << "Erreur chargement explosion.wav" << std::endl;}
    if(!this->_buffer_attaques[1].loadFromFile("Sons/laser.wav")){std::cerr << "Erreur chargement laser.wav" << std::endl;}
    //Chargement des buffers dans les Sounds
    this->_son_attaques[0].setBuffer(this->_buffer_attaques[0]);
    this->_son_attaques[1].setBuffer(this->_buffer_attaques[1]);
    this->_son_attaques[0].setVolume(27);
    this->_son_attaques[1].setVolume(40);
}

Covidmon::~Covidmon()
{
}
// GETTEUR
Type Covidmon::get_type() const
{
    return this->_type;
}

sf::Uint16 Covidmon::get_pv_max() const
{
    return this->_pv_max;
}

sf::Uint16 Covidmon::get_pv_current() const
{
    return this->_pv_current;
}

bool Covidmon::get_est_vivant() const
{
    return this->_est_vivant;
}

//Passe par référence, renvoie l'attribut
// qui est une instance de Attaque_de_loin
Attaque_de_loin &Covidmon::get_attaque_de_loin()
{
    return this->_attaque_de_loin;
}
//Passe par référence, renvoie l'attribut
// qui est une instance de Attaque_de_pres
Attaque_de_pres &Covidmon::get_attaque_de_pres()
{
    return this->_attaque_de_pres;
}
//SETTEURS
void Covidmon::set_type(Type t)
{
    this->_type = t;
}

void Covidmon::set_pv_max(sf::Uint16 pv)
{
    this->_pv_max = pv;
}

void Covidmon::set_pv_current(sf::Uint16 pv)
{
    this->_pv_current = pv;
}

void Covidmon::set_est_vivant(bool v)
{
    this->_est_vivant = v;
}

/* Affecte au Sprite une partie de l'image avec la fonction
* sf::IntRect(debut horizontale, debut vertical, longueur,hauteur)
*/
void Covidmon::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK * this->_animation,
                                                    SIZE_BLOCK * this->_direction,
                                                    SIZE_BLOCK,
                                                    SIZE_BLOCK));
}

/*Initialise la position de l'attaque,_est_lancee est false par défaut
 * La deuxième condition (press A) permet d'activer la première  
 */
void Covidmon::attaque_de_loin(sf::RenderWindow &window, bool is_my_covidmon)
{
    //On vérifie si l'attaque est lancée
    if (this->_attaque_de_loin.get_est_lancee())
    {
        //On vérifie si elle vient d'être lancée
        if (this->_attaque_de_loin.get_just_clicked())
        {
            //Initialisation de la position
            this->_attaque_de_loin.set_position_x(this->get_position_x());
            this->_attaque_de_loin.set_position_y(this->get_position_y());
            this->_attaque_de_loin.set_direction(this->get_direction());
            // Changement de valeur pour ne plus fixer la position
            this->_attaque_de_loin.set_just_clicked(false);
            this->_son_attaques[1].play();
        }
        //Affichage et déplacement de l'attaque
        this->_attaque_de_loin.draw(window);
        this->_attaque_de_loin.move();
        this->_attaque_de_loin.animate();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && is_my_covidmon && this->_delai_attaques[1].getElapsedTime().asMilliseconds()>400)
    {
        //Limite l'enchainement d'attaque, il faut attendre 0,4 secondes
        // entre deux attaques successives
        this->_delai_attaques[1].restart();
        this->_attaque_de_loin.set_est_lancee(true);
        this->_attaque_de_loin.set_just_clicked(true);
    }
}
/*Initialise la position de l'attaque,_est_lancee est false par défaut
 * La deuxième condition (press Z) permet d'activer la première  
 */
void Covidmon::attaque_de_pres(sf::RenderWindow &window, bool is_my_covidmon)
{
    //On vérifie si l'attaque est lancée
    if (this->_attaque_de_pres.get_est_lancee())
    {
        //On vérifie si l'attaque vient d'être lancée
        if (this->_attaque_de_pres.get_just_clicked())
        {
            //Initialisation de la position : l'attaque est placée dans la direction
            // du Covidmon, condition nécessaire car elle ne se déplace pas 
            switch (this->_direction)
            {
            case Up:
                this->_attaque_de_pres.set_position_x(this->get_position_x());
                this->_attaque_de_pres.set_position_y(this->get_position_y() - SIZE_BLOCK / 2);
                break;
            case Down:
                this->_attaque_de_pres.set_position_x(this->get_position_x());
                this->_attaque_de_pres.set_position_y(this->get_position_y() + SIZE_BLOCK / 2);
                break;
            case Right:
                this->_attaque_de_pres.set_position_x(this->get_position_x() + SIZE_BLOCK / 2);
                this->_attaque_de_pres.set_position_y(this->get_position_y());
                break;
            case Left:
                this->_attaque_de_pres.set_position_x(this->get_position_x() - SIZE_BLOCK / 2);
                this->_attaque_de_pres.set_position_y(this->get_position_y());
                break;
            }
            //Changement de valeur pour ne plus fixer l'annimation
            this->_attaque_de_pres.set_just_clicked(false);
            this->_son_attaques[0].play();
        }

        this->_attaque_de_pres.lancement();
        this->_attaque_de_pres.draw(window);
        this->_attaque_de_pres.animate();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && is_my_covidmon && this->_delai_attaques[0].getElapsedTime().asMilliseconds()>800)
    {
        //Limite l'enchainement d'attaque, il faut attendre 0,4 secondes
        // entre deux attaques successives
        this->_delai_attaques[0].restart();
        this->_attaque_de_pres.set_est_lancee(true);
        this->_attaque_de_pres.set_just_clicked(true);
    }
}


void Covidmon::operator-=(sf::Uint16 degats)
{
    if (this->_pv_current >= degats)
        this->_pv_current = this->_pv_current - degats;
    else
        this->_pv_current = 0;
}
//Définit les forces er faiblesses pour chaque type
//Fonction utilisée dans le choix du coefficient receive_degats 
bool Covidmon::est_faible_contre(const Covidmon &P) const
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
bool Covidmon::est_fort_contre(const Covidmon &P) const
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
// Modification des pv après contact attaque
void Covidmon::receive_degat(Covidmon &P)
{   
    // Affecte un coefficient multiplicateur
    // selon les faiblesses et forces
    if (this->est_faible_contre(P))
    {
        if (this->_attaque_de_loin.get_est_lancee())
            P -= 0.75 * this->_attaque_de_loin.get_degats();
        if (this->_attaque_de_pres.get_est_lancee())
            P -= 0.75 * this->_attaque_de_pres.get_degats();
    }
    else if (this->est_fort_contre(P))
    {
        if (this->_attaque_de_loin.get_est_lancee())
            P -= 1.25 * this->_attaque_de_loin.get_degats();
        if (this->_attaque_de_pres.get_est_lancee())
            P -= 1.25 * this->_attaque_de_pres.get_degats();
    }
    else
    {
        if (this->_attaque_de_loin.get_est_lancee())
            P -= this->_attaque_de_loin.get_degats();
        if (this->_attaque_de_pres.get_est_lancee())
            P -= this->_attaque_de_pres.get_degats();
    }
    // Surcharge d'opérateur -= pour retirer des pv
    // On modifie l'attribut est_vivant 
    if (P.get_pv_current() == 0)
        P.set_est_vivant(false);
}

// Gestion de la récéption d'une attaque
// par le covidmon adverse
void Covidmon::collision_attaque(Covidmon &P)
{
    // Comparaison des distances entre l'attaque et le Covidmon
    if (this->_attaque_de_loin.distance(P) < SIZE_BLOCK / 3)
    {
        if (!this->_attaque_de_loin.get_just_clicked())
        {
            this->receive_degat(P);
            this->_attaque_de_loin.set_est_lancee(false);
        }
        // Pour que la fonction ne s'active qu'une fois
        this->_attaque_de_loin.set_just_clicked(true);
    }

    if (this->_attaque_de_pres.distance(P) < SIZE_BLOCK)
    {
        if (!this->_attaque_de_pres.get_just_clicked())
        {
            this->receive_degat(P);
            this->_attaque_de_pres.set_est_lancee(false);
        }
        // Pour que la fonction ne s'active qu'une fois
        this->_attaque_de_pres.set_just_clicked(true);
    }
}

//Affichage de la barre de vie au dessus de l'image
void Covidmon::draw_pv(sf::RenderWindow &window)
{
    //L'attribut barre désigne quelle image afficher en fonction des pv restants
    //Le découpage est détaillé sur l'image vie2.png
    if (100 * this->get_pv_current() / this->get_pv_max() >= 100)    {this->_bar = 0;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 92){this->_bar = 1;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 85){this->_bar = 2;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 78){this->_bar = 3;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 71){this->_bar = 4;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 64){this->_bar = 5;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 57){this->_bar = 6;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 42){this->_bar = 7;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 35){this->_bar = 8;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 28){this->_bar = 9;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 21){this->_bar = 10;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 14){this->_bar = 11;}
    else if (100 * this->get_pv_current() / this->get_pv_max() >= 7 ){this->_bar = 12;}
    else                                                             {this->_bar = 13;}
    // Chargement du sprite_pv pour la barre et affichage
    this->__sprite_pv.setTextureRect(sf::IntRect(0,
                                                 this->_bar * LARGEUR_VIE,
                                                 LONGUEUR_VIE,
                                                 LARGEUR_VIE));
    this->__sprite_pv.setPosition(this->get_position_x(), this->get_position_y() - SIZE_BLOCK / 4);
    //Calcul et affichage du pourcentage de vie restant
    sf::Uint16 percent_pv = 100 * this->get_pv_current() / this->get_pv_max();
    sf::Text text(std::to_string(percent_pv) + "%", _font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);
    // On le place au dessus de la barre
    text.setPosition(sf::Vector2f(this->get_position_x() + SIZE_BLOCK / 3, this->get_position_y() - SIZE_BLOCK / 2));
    window.draw(text);
    window.draw(this->__sprite_pv);
}

// Gestion de la selection/ calcul de distance 
// avec le curseur au moment du click
void Covidmon::got_a_clic(sf::RenderWindow &window)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    sf::Uint16 dx = pos.x - this->__position_x;
    sf::Uint16 dy = pos.y - this->__position_y;
    bool collision_x = dx < SIZE_BLOCK;
    bool collision_y = dy < SIZE_BLOCK;
    //Les 2 conditions sont respectées si le curseur est sur la case du Covidmon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (collision_x && collision_y)
            _choisi = true;
        else
            _choisi = false;
    }
}
//Affiche le nom de l'instance choisie
//Charge le text avec la classe text de SFML
void Covidmon::print_name(sf::RenderWindow &window)
{
    sf::Text text("Covidmon choisi : " + this->get_nom(), _font);
    text.setCharacterSize(15);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 6));
    window.draw(text);
}

//Déplacements : se limite aux bordures d'arene
// définies au préalables
void Covidmon::_move_up()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        // Change l'animation à chaque pas
        // limitée à 3 car 4 animations par ligne
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
        //Le clock permet de rendre le mouvement plus fluide
        //et evite un enchainement d'image trop rapide
    }
    this->_direction = Up;
    if (this->__position_y > ARENE_START)
        this->__position_y -= this->_speed;
}

void Covidmon::_move_down()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        // Change l'animation à chaque pas
        // limitée à 3 car 4 animations par ligne
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        this->_clock.restart();
        //Le clock permet de rendre le mouvement plus fluide
        //et evite un enchainement d'image trop rapide
    }
    this->_direction = Down;
    if (this->__position_y < ARENE_END - SIZE_BLOCK)
        this->__position_y += this->_speed;
}

void Covidmon::_move_right()
{
    if (this->_clock.getElapsedTime().asSeconds() > 0.10f)
    {
        // Change l'animation à chaque pas
        // limitée à 3 car 4 animations par ligne
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        //Le clock permet de rendre le mouvement plus fluide
        //et evite un enchainement d'image trop rapide
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
        // Change l'animation à chaque pas
        // limitée à 3 car 4 animations par ligne
        if (this->_animation < 3)
            this->_animation++;
        else
            this->_animation = 0;
        //Le clock permet de rendre le mouvement plus fluide
        //et evite un enchainement d'image trop rapide
        this->_clock.restart();
    }
    this->_direction = Left;
    if (this->__position_x > ARENE_START)
        this->__position_x -= this->_speed;
}
