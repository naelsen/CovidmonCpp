#include "Game.hh"

Game::Game():
_current_background(menu),
_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Le monde d'apres ...")
{
	this->_backgrounds.insert(couple("menu",Image("Images/Backgrounds/menu.png")));
	this->_backgrounds.insert(couple("choix_personnage",Image("Images/Backgrounds/choix_personnage.png")));
	this->_backgrounds.insert(couple("choix_pokemon",Image("Images/Backgrounds/choix_pokemon.png")));
	this->_backgrounds.insert(couple("arene",Image("Images/Backgrounds/arene.png")));
    
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_gaby.png"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_joelle.png"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_red.png"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_chauve.png"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_butch.png"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_cassidy.png"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_cyrus.png"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_james.png"));
	// Placement des personnages sur la carte
	int i = 1;
	int j = 1;
	for(auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
	{
		if(i <= 4)
		{
			it->set_position_x(i*WINDOW_WIDTH/6);
			it->set_position_y(100.f);
			i++;
		}
		else
		{
			it->set_position_x(j*WINDOW_WIDTH/6);
			it->set_position_y(700.f - SIZE_HEIGHT_DRESSEUR);
			j++;
		}
	}

	this->_window.setFramerateLimit(60);
}

Game::~Game()
{
}

bool Game::_get_current_background() const
{
	return this->_current_background;
}

void Game::_set_current_background(Bg bg)
{
	this->_current_background = bg;
}

void Game::run()
{
	while (this->_window.isOpen())
    {
        // ==ON S'OCCUPE DE SAVOIR SI ON DOIT FERMER LA window==
        while (this->_window.pollEvent(this->_event))
        {
            if (this->_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                this->_window.close();
            }
        }
		this->_choisir_dresseur();
        this->_window.clear();
        this->_manage();
		this->_window.clear();
		this->_draw();
    	this->_window.display();
    }
}

void Game::_draw()
{
	this->_draw_bg();
	this->_draw_dresseur();
}

void Game::_draw_bg()
{
	if(this->_current_background == menu)
		this->_backgrounds["menu"].draw(this->_window);
	if(_current_background==choix_personnage)
		this->_backgrounds["choix_personnage"].draw(this->_window);
	if(this->_current_background == choix_pokemon)
		this->_backgrounds["choix_pokemon"].draw(this->_window);
	if(_current_background==arene)
		this->_backgrounds["arene"].draw(this->_window);
}

void Game::_draw_dresseur()
{
	if(this->_current_background == choix_personnage)
	{
		for(auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			it->draw(this->_window);
			it->_animate();
		}
	}

}

void Game::_manage()
{
	this->_manage_bg();
	this->_manage_dresseur();
}

void Game::_manage_bg()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && _current_background==menu)
		this->_current_background = choix_personnage;
}

void Game::_manage_dresseur()
{
	if(this->_current_background==choix_personnage)
	{
		for(auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if(it->get_choisi())
				it->move();
		}
	}
}

void Game::_choisir_dresseur()
{
	for(auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
	{
		it->got_a_clic(this->_window);
	}
}