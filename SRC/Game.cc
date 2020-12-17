#include "Game.hh"

Game::Game():
_current_background(menu),
_selec(false),
_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LE MONDE D'APRÈS ...")
{
	this->_backgrounds.insert(couple("intro",Image("Images/Backgrounds/Intro.png")));
	this->_backgrounds.insert(couple("menu",Image("Images/Backgrounds/Intro.png")));
	this->_backgrounds.insert(couple("choix_personnage",Image("Images/Backgrounds/choix_personnage.png")));
	this->_backgrounds.insert(couple("choix_pokemon",Image("Images/Backgrounds/choix_pokemon.png")));
	this->_backgrounds.insert(couple("arene",Image("Images/Backgrounds/arene.png")));
    
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_gaby.png","gaby"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_joelle.png","joelle"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_red.png","red"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_chauve.png","le chauve"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_butch.png","butch"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_cassidy.png","cassidy"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_cyrus.png","cyrus"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/R_james.png","james"));

	this->_pokemons.push_back(Pokemon("Images/Pokemons/articodin.png" ,"Articodin" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/canartichaud.png" ,"Canartichaud" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/darumaka.png" ,"Darumaka" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/feneukin.png" ,"Feneukin" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/galacvole.png" ,"Galacvole" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/galarian.png" ,"Galarian" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/gardevoir.png" ,"Gardevoir" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/gloupix.png" ,"Gloupix" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/lubegon.png" ,"Lubegon" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/mageau.png" ,"Mageau" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/mrmime.png" ,"Mrmime" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/noixbat.png" ,"NoixBat" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/oh-oh.png" ,"Oh-Oh" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/pandours.png" ,"Pandours" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/ponyta.png" ,"Ponyta" ));
	this->_pokemons.push_back(Pokemon("Images/Pokemons/skeleton.png" ,"Skeleton" )); 
	// Placement des personnages sur la carte
	sf::Uint16 i = 1;
	sf::Uint16 j = 1;
	for(auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
	{
		if(i <= 4)
		{
			it->set_position_x(i*WINDOW_WIDTH/6);
			it->set_position_y(85.f);
			i++;
		}
		else
		{
			it->set_position_x(j*WINDOW_WIDTH/6);
			it->set_position_y(620.f - SIZE_HEIGHT_PERSO);
			j++;
		}
	}
	//Placement des pokémons
	i = 1;
	j = 1;
	sf::Uint16 k = 1;
	sf::Uint16 l = 1;
	for(auto it = this->_pokemons.begin(); it != this->_pokemons.end(); it++)
	{
		if(i <= 4)
		{
			it->set_position_x(i*WINDOW_WIDTH/6);
			it->set_position_y(25.f);
			i++;
		}
		else if(j <= 4)
		{
			it->set_position_x(j*WINDOW_WIDTH/6);
			it->set_position_y(85.f);
			j++;
		}
		else if(k <= 4)
		{
			it->set_position_x(k*WINDOW_WIDTH/6);
			it->set_position_y(620.f - SIZE_BLOCK_POKEMON);
			k++;
		}
		else if(l <= 4)
		{
			it->set_position_x(l*WINDOW_WIDTH/6);
			it->set_position_y(690.f - SIZE_BLOCK_POKEMON);
			l++;
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
        this->_manage();
		this->_draw();
    	this->_window.display();
    }
}

void Game::_draw()
{
	this->_draw_bg();
	this->_draw_dresseur();
	this->_draw_pokemon();
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
			it->animate();
		}
	}
	if(this->_current_background == choix_pokemon)
	{
		for(auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if(it->get_choisi())
			{
				it->draw(this->_window);
				it->animate();
			}
		}
	}
}

void Game::_draw_pokemon()
{
	if(this->_current_background == choix_pokemon)
	{
		for(auto it = this->_pokemons.begin(); it != this->_pokemons.end(); it++)
		{
				it->draw(this->_window);
				it->animate();
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && _current_background==intro)
		_set_current_background(menu);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && _current_background==menu)
		_set_current_background(choix_personnage);

	for(auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
	{
		if(it->is_out())
		{
			_set_current_background(choix_pokemon);
			it->set_position_x(0);
			it->set_position_y(WINDOW_HEIGHT/2);
		}
	}
}

void Game::_manage_dresseur()
{
	if(this->_current_background==choix_personnage)
	{
		for(auto it = this->_players.begin(); it != this->_players.end(); it++)
		{
			it->send();
			it->receive(this->_dresseurs);
			it->get_dresseur()->move();
		}
	}
	if(this->_current_background==choix_pokemon)
		this->_players[0].get_dresseur()->move();
}

void Game::_choisir_dresseur()
{
	if(this->_selec==false)
	{
		for(auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			it->got_a_clic(this->_window);
			if(it->get_choisi())
			{
				Player P(*it);
				this->_selec = true;
				this->_players.push_back(P);
			}
		}
	}
}