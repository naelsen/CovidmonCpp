#include "Attaque_de_pres.hh"

//Constructeur utilisé dans Covidmon, attribut les mêmes valeurs par défaut
Attaque_de_pres::Attaque_de_pres(std::string im) : Image(im),
                                                   _degats(50),
                                                   _animation(0),
                                                   _est_lancee(false),
                                                   _just_clicked(true)
{
}
// Constructeur par défaut
Attaque_de_pres::Attaque_de_pres() : _degats(50)
{
}
// Constructeur par copie
Attaque_de_pres::Attaque_de_pres(Attaque_de_pres const &at) : Image(at),
                                                              _degats(at._degats),
                                                              _animation(at._animation),
                                                              _est_lancee(at._est_lancee),
                                                              _just_clicked(true)

{
}
// Destructeur
Attaque_de_pres::~Attaque_de_pres()
{
}
// GETTEURS
int Attaque_de_pres::get_degats() const
{
    return this->_degats;
}

bool Attaque_de_pres::get_est_lancee() const
{
    return this->_est_lancee;
}

bool Attaque_de_pres::get_just_clicked() const
{
    return this->_just_clicked;
}

sf::Uint16 Attaque_de_pres::get_animation() const
{
    return this->_animation;
}
// SETTEURS
void Attaque_de_pres::set_degats(int d)
{
    this->_degats = d;
}

void Attaque_de_pres::set_est_lancee(bool e)
{
    this->_est_lancee = e;
}

void Attaque_de_pres::set_just_clicked(bool click)
{
    this->_just_clicked = click;
}

void Attaque_de_pres::set_animation(sf::Uint16 animation)
{
    this->_animation = animation;
}

/* Affecte au Sprite une partie de l'image avec la fonction
 * sf::IntRect(debut horizontale, debut vertical, longueur,hauteur)
 * les images sont placés sur une seule ligne (voir fichier explosion_eau.png)
 * par exemple, comme l'image est fixe, on la remplace par la suivante à la méme position
 */
void Attaque_de_pres::animate()
{
    this->__sprite_image.setTextureRect(sf::IntRect(SIZE_BLOCK * this->_animation,
                                                    0,
                                                    SIZE_BLOCK,
                                                    SIZE_BLOCK));
}

/* La position est initialisée à celle de l'instance 
 * à laquelle elle appartient selon les cas, on appelle une */
void Attaque_de_pres::lancement()
{
  if (this->_clock.getElapsedTime().asSeconds() > 0.05f)
  {
    // Le fichier image contient 16 animations
    // On les affiche succesivement toutes les 0.05 secondes
    if (this->_animation < 15)
        this->_animation++;
    else
    {
      //Une fois l'animation términée on arrete d'afficher
      // et on la déplace hors fenêtre pour eviter d'autres collisions
      this->_animation = 0;
      set_est_lancee(false);
      this->set_just_clicked(true);
      this->set_position_x(WINDOW_WIDTH);
    }
    //Le clock permet de rendre le mouvement plus fluide
    //et evite un enchainement d'image trop rapide
    this->_clock.restart();
  }
}