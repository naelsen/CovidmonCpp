#include "Game.hh"

Game::Game() : _current_background(intro),
			   _selec_dresseur(false),
			   _selec_covidmon(false),
			   _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LE MONDE D'APRES ...")
{
	this->_font.loadFromFile("Images/arial.ttf");
	this->_text.setFont(this->_font);
	this->_text.setString("Choisissez un joueur \n   (avec la souris!)");
	this->_text.setCharacterSize(17);
	this->_text.setStyle(sf::Text::Bold);
	this->_text.setFillColor(sf::Color::Black);
	this->_text.setPosition(sf::Vector2f(245, 220));

	this->_backgrounds.insert(couple("intro", Image("Images/Backgrounds/intro3.png")));
	this->_backgrounds.insert(couple("menu", Image("Images/Backgrounds/menu.png")));
	this->_backgrounds.insert(couple("choix_personnage", Image("Images/Backgrounds/choix_personnage.png")));
	this->_backgrounds.insert(couple("choix_covidmon", Image("Images/Backgrounds/choix_covidmon.png")));
	this->_backgrounds.insert(couple("arene", Image("Images/Backgrounds/arene.png")));

	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_charo.png", "Charo"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_tantine.png", "Tantine"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_tchang.png", "Tchang"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/G_zepekenio.png", "Zepekenio"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/M_magelan.png", "Magelan"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/M_magman.png", "Magman"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/M_toto.png", "Toto"));
	this->_dresseurs.push_back(Dresseur("Images/Personnages/M_zepekenia.png", "Zepekenia"));

	this->_covidmons.push_back(Covidmon("Images/Covidmons/E_galarian.png", "Galarian", Eau));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/E_leviator.png", "Leviator", Eau));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/E_mewtoo.png", "Mewtoo", Eau));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/E_tortank.png", "Tortank", Eau));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/F_camerupt.png", "Camerupt", Feu));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/F_darumaka.png", "Darumaka", Feu));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/F_dracofeu.png", "Dracofeu", Feu));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/F_incinerator.png", "Incinerator", Feu));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/P_chierbe.png", "Chierbe", Plante));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/P_gardevoir.png", "Gardevoir", Plante));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/P_herbiossa.png", "Herbiossa", Plante));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/P_pandours.png", "Pandours", Plante));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/V_articodin.png", "Articodin", Vol));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/V_galacvole.png", "Galacvole", Vol));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/V_lubegon.png", "Lubegon", Vol));
	this->_covidmons.push_back(Covidmon("Images/Covidmons/V_oh-oh.png", "Oh-oh", Vol));
	// Placement des personnages sur la carte
	sf::Uint16 i = 1;
	sf::Uint16 j = 1;
	for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
	{
		if (i <= 4)
		{
			it->set_position_x(i * WINDOW_WIDTH / 6);
			it->set_position_y(85.f);
			i++;
		}
		else
		{
			it->set_position_x(j * WINDOW_WIDTH / 6);
			it->set_position_y(620.f - SIZE_HEIGHT_PERSO);
			j++;
		}
	}
	//Placement des pokémons
	i = 1;
	j = 1;
	sf::Uint16 k = 1;
	sf::Uint16 l = 1;
	for (auto it = this->_covidmons.begin(); it != this->_covidmons.end(); it++)
	{
		if (i <= 4)
		{
			it->set_position_x(i * WINDOW_WIDTH / 6);
			it->set_position_y(25.f);
			i++;
		}
		else if (j <= 4)
		{
			it->set_position_x(j * WINDOW_WIDTH / 6);
			it->set_position_y(85.f);
			j++;
		}
		else if (k <= 4)
		{
			it->set_position_x(k * WINDOW_WIDTH / 6);
			it->set_position_y(620.f - SIZE_BLOCK);
			k++;
		}
		else if (l <= 4)
		{
			it->set_position_x(l * WINDOW_WIDTH / 6);
			it->set_position_y(690.f - SIZE_BLOCK);
			l++;
		}
	}
	sf::Clock c1;
	sf::Clock c2;
	sf::Sound s1;
	sf::Sound s2;
	sf::SoundBuffer sb1;
	sf::SoundBuffer sb2;
	bool sound_switched1 = false;
	bool sound_switched2 = false;
	this->_clocks.push_back(c1);
	this->_clocks.push_back(c2);
	this->_sounds_switched.push_back(sound_switched1);
	this->_sounds_switched.push_back(sound_switched2);
	this->_clocks[0].restart();
	this->_clocks[1].restart();
	this->_window.setFramerateLimit(60);
}

Game::~Game()
{
}

Bg Game::_get_current_background() const
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
		// ==ON S'OCCUPE DE SAVOIR SI ON DOIT FERMER LA FENETRE
		while (this->_window.pollEvent(this->_event))
		{
			if (this->_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->_window.close();
				this->_players[0].disconnect();
			}
		}
		this->_choisir_dresseur();
		this->_choisir_covidmon();
		this->_draw();
		this->_manage();
		this->_window.display();
	}
}

void Game::_draw()
{
	this->_draw_bg();
	this->_draw_dresseur();
	this->_draw_covidmon();
	if (this->_selec_covidmon)
		this->_players[0].pop_pokeball(this->_window);
}

void Game::_draw_bg()
{
	switch (this->_current_background)
	{
	case intro:
		this->_backgrounds["intro"].draw(this->_window);
		break;
	case menu:
		this->_backgrounds["menu"].draw(this->_window);
		break;
	case choix_personnage:
		this->_backgrounds["choix_personnage"].draw(this->_window);
		if (this->_selec_dresseur == false)
			this->_window.draw(this->_text);
		break;
	case choix_covidmon:
		this->_backgrounds["choix_covidmon"].draw(this->_window);
		if (this->_selec_covidmon == false)
			this->_window.draw(this->_text);
		break;
	case arene:
		this->_backgrounds["arene"].draw(this->_window);
		break;
	default:
		break;
	}
}

void Game::_draw_dresseur()
{
	if (this->_current_background == choix_personnage)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
			}
			if (it->get_current_bg() == choix_personnage)
			{
				it->draw(this->_window);
				it->animate();
			}
		}
	}
	if (this->_current_background == choix_covidmon)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
			}
			if (it->get_current_bg() == choix_covidmon)
			{
				it->draw(this->_window);
				it->animate();
			}
		}
	}
	if (this->_current_background == arene)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
				it->draw(this->_window);
				it->animate();
			}
			if (it->get_current_bg() == arene)
			{
				it->draw(this->_window);
				it->animate();
			}
		}
	}
}

void Game::_draw_covidmon()
{
	if (this->_current_background == choix_covidmon)
	{
		for (auto it = this->_covidmons.begin(); it != this->_covidmons.end(); it++)
		{
			if (!it->get_choisi())
			{
				it->draw(this->_window);
				it->animate();
			}
			else if (it->distance(*this->_players[0].get_dresseur()) > 20 && !_selec_covidmon)
			{
				it->draw(this->_window);
				it->print_name(this->_window);
			}
		}
	}
	if (this->_current_background == arene)
	{
		for (auto it = this->_covidmons.begin(); it != this->_covidmons.end(); it++)
		{
			if (it->get_choisi() && it->get_est_vivant())
			{
				it->print_name(this->_window);
				it->draw(this->_window);
				it->animate();
				it->draw_pv(this->_window);
			}
			if (it->get_current_bg() == arene && it->get_est_vivant())
			{
				it->draw(this->_window);
				it->animate();
			}
		}
		if(_players[0].get_covidmon().size() == 2)
		{
			_players[0].get_covidmon()[1]->draw_pv(this->_window);
		}
	}
}
void Game::_manage()
{
	this->_manage_bg();
	this->_manage_sound();
	this->_manage_dresseur();
	//this->_manage_pokemon();
}

void Game::_back_sound()
{
	if (this->_current_background == intro)
	{
		if (this->_sounds_switched[1] == false)
		{
			if (!this->_sound_back.openFromFile("Sons/intro.wav"))
				std::cout << "Erreur lors de l'ouverture de Sons/intro.wav" << std::endl;
			this->_sounds_switched[1] = true;
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
		else if (this->_clocks[1].getElapsedTime().asSeconds() > 41)
		{
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
	}
	else if (this->_current_background != arene)
	{
		if (this->_sounds_switched[1] == true)
		{
			if (!this->_sound_back.openFromFile("Sons/menu_and_choix.wav"))
				std::cout << "Erreur lors de l'ouverture de Sons/menu_and_choix.wav" << std::endl;
			this->_sounds_switched[1] = false;
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
		else if (this->_clocks[1].getElapsedTime().asSeconds() > 19)
		{
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
	}
	else
	{
		if (this->_sounds_switched[1] == false)
		{
			if (!this->_sound_back.openFromFile("Sons/musique_arene1.wav"))
				std::cout << "Erreur lors de l'ouverture de Sons/musique_arene1.wav" << std::endl;
			this->_sounds_switched[1] = true;
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
		else if (this->_clocks[1].getElapsedTime().asSeconds() > 180)
		{
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
	}
}

void Game::_front_sound()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->_current_background != arene && this->_clocks[0].getElapsedTime().asMilliseconds() > 200)
	{
		if (this->_sounds_switched[0] == false)
		{
			if (!this->_sound_front.openFromFile("Sons/b.wav"))
				std::cout << "Erreur lors de l'ouverture de Sons/b.wav" << std::endl;
			this->_sounds_switched[0] = true;
			this->_clocks[0].restart();
			this->_sound_front.play();
		}
	}
	else if (this->_players[0].is_moving() && this->_clocks[0].getElapsedTime().asMilliseconds() > 800)
	{
		if (this->_sounds_switched[0] == true)
		{
			if (!this->_sound_front.openFromFile("Sons/footstep.wav"))
				std::cout << "Erreur lors de l'ouverture de Sons/footstep.wav" << std::endl;
			this->_sounds_switched[0] = false;
			this->_clocks[0].restart();
			this->_sound_front.play();
		}
		else
		{
			this->_clocks[0].restart();
			this->_sound_front.play();
		}
	}
}

void Game::_manage_sound()
{
	this->_back_sound();
	this->_front_sound();
}

void Game::_manage_bg()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->_current_background == intro)
	{
		_set_current_background(menu);
		this->_clocks[0].restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->_current_background == menu)
	{
		if (this->_clocks[0].getElapsedTime().asMilliseconds() > 200)
			_set_current_background(choix_personnage);
	}
	else if (this->_selec_dresseur)
	{
		if (this->_players[0].get_dresseur()->is_out())
		{
			if (this->_current_background == choix_personnage)
			{
				_set_current_background(choix_covidmon);
				this->_players[0].get_dresseur()->set_current_bg(choix_covidmon);
			}
			else if (this->_current_background == choix_covidmon)
			{
				_set_current_background(arene);
				this->_players[0].get_dresseur()->set_current_bg(arene);
				this->_players[0].get_covidmon()[0]->set_current_bg(arene);
			}
			this->_players[0].get_dresseur()->set_position_x(0);
		}
	}
}
void Game::_manage_dresseur()
{
	if (this->_current_background == choix_personnage)
	{
		for (auto it = this->_players.begin(); it != this->_players.end(); it++)
		{
			it->send();
			it->receive(this->_dresseurs);
			it->get_dresseur()->move();
		}
	}
	if (this->_current_background == choix_covidmon)
	{
		this->_players[0].send();
		this->_players[0].receive(this->_dresseurs);
		this->_players[0].get_dresseur()->move();
		_manage_covidmon();
	}
	if (this->_current_background == arene)
	{
		if (this->_players[0].get_dresseur()->get_position_y() != WINDOW_WIDTH / 2 - 100 && this->_players[0].get_dresseur()->get_animation() != 0)
		{
			this->_players[0].get_dresseur()->set_position_y(WINDOW_WIDTH / 2 - 100);
			this->_players[0].get_dresseur()->set_animation(0);
			this->_players[0].send();
			this->_players[0].receive(this->_dresseurs);
		}
		else
		{
			_manage_covidmon();
		}

		if (!this->_players[0].get_first_on_arene())
		{
			this->_players[0].get_dresseur()->set_direction(Left);
			this->_players[0].get_dresseur()->set_position_x(WINDOW_WIDTH - SIZE_WIDTH_PERSO);
		}
	}
}

void Game::_manage_covidmon()
{
	if (this->_current_background == arene)
	{
		this->_players[0].send_covidmon();
		this->_players[0].receive(this->_covidmons, this->_window);
		if(this->_players[0].get_covidmon()[0]->get_est_vivant())
		{
			this->_players[0].get_covidmon()[0]->move();
			this->_players[0].get_covidmon()[0]->attaque_de_loin(this->_window);
			this->_players[0].get_covidmon()[0]->attaque_de_pres(this->_window);
		}
		if(this->_players[0].get_covidmon().size() == 2)
		{
			if(this->_players[0].get_covidmon()[1]->get_est_vivant())
			{
				this->_players[0].get_covidmon()[1]->attaque_de_loin(this->_window);
				this->_players[0].get_covidmon()[1]->attaque_de_pres(this->_window);
			}
			this->_players[0].get_covidmon()[1]->collision_attaque(*(this->_players[0].get_covidmon()[0]));
			this->_players[0].get_covidmon()[0]->collision_attaque(*(this->_players[0].get_covidmon()[1]));
		}
	}
}

void Game::_choisir_dresseur()
{
	if (!this->_selec_dresseur && this->_current_background == choix_personnage)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			it->got_a_clic(this->_window);
			if (it->get_choisi())
			{
				Player P(*it);
				this->_players.push_back(P);
				if (_players[0].is_accepted())
				{
					this->_selec_dresseur = true;
					this->_text.setString("Choisissez un covidmon \n   (avec la souris!)");
				}
				else
				{
					_players.pop_back();
					it->set_choisi(false);
				}
			}
		}
	}
}

void Game::_choisir_covidmon()
{
	if (!this->_selec_covidmon && this->_current_background == choix_covidmon)
	{
		for (auto it = this->_covidmons.begin(); it != this->_covidmons.end(); it++)
		{
			it->got_a_clic(this->_window);
			if (it->get_choisi())
			{
				if (this->_players[0].get_dresseur()[0].distance(*it) > 10)
				{
					this->_text.setString("Capture du Covidmon, rapprochez \nvous de la case le recuperer !");
					this->_window.draw(this->_text);
				}
				else
				{
					this->_players[0].set_covidmon(*it);
					this->_selec_covidmon = true;
				}
			}
		}
	}
}