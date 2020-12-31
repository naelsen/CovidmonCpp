#include "Game.hh"

// Constructeur
Game::Game() : _port(30001),
			   _IP("local"),
			   _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LE MONDE D'APRES ...")
{
	this->_build();
}

Game::Game(short int port) : _port(port),
							 _IP("local"),
							 _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LE MONDE D'APRES ...")
{
	this->_build();
}

Game::Game(short int port, std::string IP) : _port(port),
											 _IP(IP),
							 				 _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LE MONDE D'APRES ...")
{
	this->_build();
}

// Destrcuteur
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
			// Si on appuie sur echap ou sur la croix en haut a droite on se deconnecte et on ferme la fenetre
			if (this->_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->_window.close();
				this->_players[0].disconnect();
			}
		}
		// attend un clic pour initialisé le player et donc se connecter au serveur
		this->_choisir_dresseur();
		// attend un clic pour choisir son covidmon
		this->_choisir_covidmon();
		// On dessine les dresseur, covidmons, backgrounds
		this->_draw();
		// Gere les actions de pokemon et dresseur + communication serveur
		this->_manage();
		// Verifie si un joueur a gagner, on anonce la victoire ou défaite
		this->_check_end();
		// Commande pour les combats de covidmons
		this->_show_commande();
		// On affiche ce qui à été draw
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
	// Affiche le background correspondant à l'endroit ou on se trouve
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
		// On parcours les dresseurs afins de savoir si ils ont été choisi
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
			}
			// On dessine les dresseurs qui sont dans ce background
			// on ne dessine pas que celui qu'on a choisi car il y a celui 
			// de notre adversaire a dessiner
			if(it->get_current_bg() == choix_personnage)
			{
				it->draw(this->_window);
				// Permet de mettre le bon carré de sprite nécessaire à l'animation
				it->animate();
			}
		}
	}
	// Si on est dans le background ou il y a les covidmons
	else if (this->_current_background == choix_covidmon)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			//On affiche le nom du dresseur qu'on a choisi sur l'ecran
			if (it->get_choisi())
			{
				it->print_name(this->_window);
			}
			// On dessine les dresseurs qui sont dans choix_covidmon
			if(it->get_current_bg() == choix_covidmon)
			{
				it->draw(this->_window);
				it->animate();
			}
		}
	}
	// Meme fonctionnement
	else if (this->_current_background == arene)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			if (it->get_choisi())
			{
				it->print_name(this->_window);
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
	// Lorsqu'on est dans le choix des covidmons
	if (this->_current_background == choix_covidmon)
	{
		for (auto it = this->_covidmons.begin(); it != this->_covidmons.end(); it++)
		{
			// On print les covidmons que l'on a pas choisi
			if(!it->get_choisi())
			{
				it->draw(this->_window);
				it->animate();
			}
			// On affiche le covidmon entre le moment on on a cliqué et ou on se deplace sur lui (la capture)
			// on precise de plus son nom afin de bien voir si on ne s'est pas tromper avant de le capturer
			else if (it->get_choisi() && it->distance(*this->_players[0].get_dresseur()) > 20 && !_selec_covidmon)
			{
				it->draw(this->_window);
				it->print_name(this->_window);
			}
		}
	}
	if (this->_current_background == arene)
	{
		// Si mon pokemon est vivant
		if (this->_players[0].get_covidmon()[0]->get_est_vivant())
		{
			this->_players[0].get_covidmon()[0]->print_name(this->_window);
			this->_players[0].get_covidmon()[0]->draw(this->_window);
			this->_players[0].get_covidmon()[0]->animate();
			// On affiche sa barre de pv
			this->_players[0].get_covidmon()[0]->draw_pv(this->_window);
		}
		// Lorsque on est deux dans l'arene on peut draw le covidmon adverse (this->_players[0].get_covidmon()[1])
		// si on avait pas precisé : this->_players[0].get_covidmon().size() == 2, il y aurait eu
		// une erreur de segmentation car on essaye d'acceder a un element du vecteur qui n'a pas ete instancié
		if (this->_players[0].get_covidmon().size() == 2 && this->_players[0].get_covidmon()[1]->get_est_vivant())
		{
			this->_players[0].get_covidmon()[1]->draw(this->_window);
			this->_players[0].get_covidmon()[1]->animate();
			this->_players[0].get_covidmon()[1]->draw_pv(this->_window);
		}
	}
}

// Gestion du sons de fond
void Game::_back_sound()
{
	// Lorsqu'on est a l'intro
	if (this->_current_background == intro)
	{
		// Au debut on est obligé d'etre est false car on l'a instancier comme ca
		if (this->_sounds_switched[1] == false)
		{
			// On lit ouvre le son. On a pas utiliser BufferSound car il aurait fallu le charger en memoire
			// et pour chaque son ca prend du temps si le son est long
			if (!this->_sound_back.openFromFile("Sons/intro.wav"))
				std::cout << "Erreur lors de l'ouverture de Sons/intro.wav" << std::endl;
			// On passe a false car le son tourne en boucle et on ne veut pas l'ouvrir plusieur fois 
			this->_sounds_switched[1] = true;
			this->_clocks[1].restart();
			this->_sound_back.setVolume(20);
			this->_sound_back.play();
		}
		// Afin de recommencer a jouer le son, pour que ca se fasse en boucle
		// si on reste longtemps dans l'intro
		else if (this->_clocks[1].getElapsedTime().asSeconds() > 41)
		{
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
	}
	else if (this->_current_background != arene)
	{
		// On change de son
		// (avant on a laisser a true donc on fait la condition avec true)
		if (this->_sounds_switched[1] == true)
		{
			if (!this->_sound_back.openFromFile("Sons/menu_and_choix.wav"))
				std::cout << "Erreur lors de l'ouverture de Sons/menu_and_choix.wav" << std::endl;
			// On passe a false
			this->_sounds_switched[1] = false;
			this->_clocks[1].restart();
			this->_sound_back.setVolume(20);
			this->_sound_back.play();
		}
		// Pour que le sons se fasse en boucle
		else if (this->_clocks[1].getElapsedTime().asSeconds() > 19)
		{
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
	}
	else // Dans l'arene
	{
		// On change de son
		// (avant on a laisser a false donc on fait la condition avec false)
		if (this->_sounds_switched[1] == false)
		{
			if (!this->_sound_back.openFromFile("Sons/musique_arene1.wav"))
				std::cout << "Erreur lors de l'ouverture de Sons/musique_arene1.wav" << std::endl;
			// On passe a true
			this->_sounds_switched[1] = true;
			this->_sound_back.setVolume(20);
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
		// Pour la boucle
		else if (this->_clocks[1].getElapsedTime().asSeconds() > 180)
		{
			this->_clocks[1].restart();
			this->_sound_back.play();
		}
	}
}

// Meme fonctionnement que backsound mais avec this->_sound_switched[0] et this->_clocks[0]
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
	else if (this->_players[0].is_moving() && this->_clocks[0].getElapsedTime().asMilliseconds() > 800 && this->_current_background != arene)
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

void Game::_manage()
{
	this->_manage_bg();
	this->_manage_sound();
	this->_manage_dresseur();
}

void Game::_manage_sound()
{
	this->_back_sound();
	this->_front_sound();
}


void Game::_manage_bg()
{
	// Lorsque on appuie sur entrée on passe de l'intro au menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->_current_background == intro)
	{
		this->_set_current_background(menu);
		this->_clocks[0].restart();
	}
	// Lorsque on appuie sur entrée on passe du menu au choix des dresseurs
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && this->_current_background == menu)
	{
		if (this->_clocks[0].getElapsedTime().asMilliseconds() > 200)
			this->_set_current_background(choix_personnage);
	}
	// Maintenabt qu'un joueur est selectionné, c'est lui qui va entrainer le changement de backgrounds
	else if (this->_selec_dresseur)
	{
		// Si il sort du background 
		if (this->_players[0].get_dresseur()->is_out())
		{
			// Si il était au choix des personnage il passe au choix des covidmons
			if (this->_current_background == choix_personnage)
			{
				this->_set_current_background(choix_covidmon);
				this->_players[0].get_dresseur()->set_current_bg(choix_covidmon);
			}
			// Si il était au choix des covidmon il passe au choix à l'arène et son covidmon aussi
			else if (this->_current_background == choix_covidmon)
			{
				this->_set_current_background(arene);
				this->_players[0].get_dresseur()->set_current_bg(arene);
				this->_players[0].get_covidmon()[0]->set_current_bg(arene);
			}
			// A chaque fois qu'il change de background on le remet en x=0 pour simuler le
			// fait qu'il passe la porte
			this->_players[0].get_dresseur()->set_position_x(0);
		}
	}
}

void Game::_manage_dresseur()
{
	if (this->_current_background == choix_personnage)
	{
		/* 
		Vous vous etes surement demander pourquoi il y a un vecteur de player alors qu'il y a qu'un player
		dans le vecteur ?
		On aurait pu mettre un booleen pour savoir si le player a été choisi mais on pensait qu'on allait mettre
		aussi le player adverse, au final on ne l'a pas fait pour diverse raisons, continuons.
		*/

		// Si le player est dans le vecteur (a été choisi) on envoie ses données au serveur et on peut bouger le dresseur choisi
		for (auto it = this->_players.begin(); it != this->_players.end(); it++)
		{
			it->send_dresseur();
			it->receive(this->_dresseurs);
			it->get_dresseur()->move();
		}
	}
	if (this->_current_background == choix_covidmon)
	{
		this->_players[0].send_dresseur();
		this->_players[0].receive(this->_dresseurs);
		this->_players[0].get_dresseur()->move();
		// On empeche au dresseur de passer la porte si il n'a pas choisi de covidmon
		if(this->_players[0].get_dresseur()->get_position_x() > WINDOW_HEIGHT - SIZE_BLOCK && !_selec_covidmon)
			this->_players[0].get_dresseur()->set_position_x(WINDOW_HEIGHT - SIZE_BLOCK);
	}
	if (this->_current_background == arene)
	{
		// Si on arrive en premier
		if (this->_players[0].get_first_on_arene() && this->_players[0].get_dresseur()->get_position_y() != WINDOW_WIDTH / 2 - 100 && this->_players[0].get_dresseur()->get_animation() != 0)
		{
			// On se place a gauche
			this->_players[0].get_dresseur()->set_position_y(WINDOW_WIDTH / 2 - 100);
			this->_players[0].get_dresseur()->set_animation(0);
			for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
			{
				// On place l'autre dresseur qui est encore dans choix_covidmon à gauche
				if(it->get_current_bg()==choix_covidmon)
				{
					std::cout << it->get_nom();
					it->set_current_bg(arene);
					it->set_position_y(WINDOW_WIDTH / 2 - 100);
					it->set_position_x(WINDOW_WIDTH - SIZE_BLOCK);
					it->set_direction(Left);
				}
			}
		}
		// Si on arrive en deuxieme
		else if (!this->_players[0].get_first_on_arene() && this->_players[0].get_dresseur()->get_position_y() != WINDOW_WIDTH / 2 - 100 && this->_players[0].get_dresseur()->get_animation() != WINDOW_WIDTH - SIZE_BLOCK)
		{
			// On se place a doite
			this->_players[0].get_dresseur()->set_direction(Left);
			this->_players[0].get_dresseur()->set_position_y(WINDOW_WIDTH / 2 - 100);
			this->_players[0].get_dresseur()->set_position_x(WINDOW_WIDTH - SIZE_BLOCK);
			for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
			{
				// On place l'autre dresseur a gauche
				// L'autre dresseur est en realite dans l'arene mais comme il nous a pas envoyer sa
				// position quand il est entrer dans l'arene il est toujours considérer comme
				// etant dans choix covidmon
				if(it->get_current_bg()==choix_covidmon)
				{
					it->set_current_bg(arene);
					it->set_position_y(WINDOW_WIDTH / 2 - 100);
					it->set_position_x(0);
					it->set_direction(Right);
				}
			}
		}
		this->_manage_covidmon();
	}
}

void Game::_manage_covidmon()
{
	// Lorsqu'on est dans l'arene
	if (this->_current_background == arene)
	{
		// On envoie les donnée de covidmon
		this->_players[0].send_covidmon();
		this->_players[0].receive(this->_covidmons, this->_window);
		// Si notre covidmon est vivant on peut attaquer et bouger
		if (this->_players[0].get_covidmon()[0]->get_est_vivant())
		{
			this->_players[0].get_covidmon()[0]->move();
			this->_players[0].get_covidmon()[0]->attaque_de_loin(this->_window, true);
			this->_players[0].get_covidmon()[0]->attaque_de_pres(this->_window, true);
		}
		// Si on est deux dans l'arene alors:
		if (this->_players[0].get_covidmon().size() == 2)
		{
			// Le covidmon adverse peut attaquer si il est vivant
			if (this->_players[0].get_covidmon()[1]->get_est_vivant())
			{
				this->_players[0].get_covidmon()[1]->attaque_de_loin(this->_window, false);
				this->_players[0].get_covidmon()[1]->attaque_de_pres(this->_window, false);
			}
			// Si les deux covidmons sont vivant alors les deux peuvent attaquer et donc il peut y avoir une collision
			if (this->_players[0].get_covidmon()[0]->get_est_vivant() && this->_players[0].get_covidmon()[1]->get_est_vivant())
			{
				this->_players[0].get_covidmon()[0]->collision_attaque(*(this->_players[0].get_covidmon()[1]));
				this->_players[0].get_covidmon()[1]->collision_attaque(*(this->_players[0].get_covidmon()[0]));
			}
		}
		// On re envoie les données apres tout les changement
		this->_players[0].send_covidmon();
		this->_players[0].receive(this->_covidmons, this->_window);
	}
}

void Game::_choisir_dresseur()
{
	// Lorsqu'on est dans le choix personnage et qu'on a pas encore choisi un dresseur.
	if (!this->_selec_dresseur && this->_current_background == choix_personnage)
	{
		for (auto it = this->_dresseurs.begin(); it != this->_dresseurs.end(); it++)
		{
			// Si le dresseur se fait cliquer dessus alors il est choisi.
			it->got_a_clic(this->_window);
			if (it->get_choisi())
			{
				// On l'instancie différement selon son ip et son port
				if(this->_port == 30001 && this->_IP == "local")
				{
					Player P(*it);
					this->_players.push_back(P);
				}
				else if(this->_port != 30001 && this->_IP == "local")
				{
					Player P(*it, this->_port);
					this->_players.push_back(P);
				}
				else if(this->_IP != "local")
				{
					Player P(*it, this->_port, this->_IP);
					this->_players.push_back(P);
				}
				// Si il est accepter on le met en tant que personnage selectionné dans game
				if (this->_players[0].is_accepted())
				{
					this->_selec_dresseur = true;
					// On charge le prochain texte pour choix_covidmon
					this->_text.setString("Choisissez un covidmon \n   (avec la souris!)");
				}
				else
				{
					// Si il est refuser on enleve le player, il devra reselectionner un autre dresseur
					this->_players.pop_back();
					it->set_choisi(false);
				}
			}
		}
	}
}

void Game::_choisir_covidmon()
{
	// Si on a pas encore choisi de covidmon
	if (!this->_selec_covidmon && this->_current_background == choix_covidmon)
	{
		for (auto it = this->_covidmons.begin(); it != this->_covidmons.end(); it++)
		{
			it->got_a_clic(this->_window);
			if (it->get_choisi())
			{
				// Tant qu'on est a plus de 4 * SIZE_BLOCK / 9, alors on a pas encore selectionné le covidmon
				if (this->_players[0].get_dresseur()[0].distance(*it) > 4 * SIZE_BLOCK / 9)
				{
					this->_text.setString("Capture du Covidmon, rapprochez \nvous de la case le recuperer !");
					this->_window.draw(this->_text);
				}
				else
				{
					// On ajoute le covidmon au player
					this->_players[0].set_covidmon(*it);
					// Le covidmon est selectionné
					this->_selec_covidmon = true;
				}
			}
		}
	}
}

void Game::_check_end()
{
	if (this->_current_background == arene)
	{
		// Si les deux covidmons sont dans l'arene
		if (this->_players[0].get_covidmon().size() == 2)
		{
			// On verifie si c'est fini
			if (this->_players[0].get_end())
			{
				// Si le player a gagner
				if (this->_players[0].get_win())
				{
					// On draw l'image de victoire
					Image win("Images/win.png");
					win.set_position_x(120);
					win.set_position_y(WINDOW_HEIGHT / 3 -20);
					win.draw(this->_window);
				}
				else // Si il a perdu
				{
					// On draw l'image de défaite
					Image loose("Images/looser.png");
					loose.set_position_x(100);
					loose.set_position_y(WINDOW_HEIGHT / 3 +20);
					loose.draw(this->_window);
				}
				// Appuyer sur entrer pour recommencer
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					this->_clean();
					this->run();
				}
				
			}
		}
	}
}

void Game::_clean()
{
	// On remet nos personnage dans le menu + on remet les attributs nécessaire
	// pour repartir de choix_covidmon
	this->_current_background = choix_covidmon;
	this->_players[0].get_covidmon()[0]->set_pv_current(this->_players[0].get_covidmon()[0]->get_pv_max());
	this->_players[0].get_covidmon()[1]->set_pv_current(this->_players[0].get_covidmon()[1]->get_pv_max());
	this->_players[0].get_covidmon()[0]->set_current_bg(choix_covidmon);
	this->_players[0].get_covidmon()[1]->set_current_bg(choix_covidmon);
	this->_players[0].get_covidmon()[0]->set_direction(Down);
	this->_players[0].get_covidmon()[1]->set_direction(Down);
	this->_players[0].get_covidmon()[0]->set_est_vivant(true);
	this->_players[0].get_covidmon()[1]->set_est_vivant(true);
	this->_players[0].get_covidmon()[1]->set_current_bg(choix_covidmon);
	this->_players[0].get_dresseur()->set_current_bg(choix_covidmon);
	this->_players[0].get_dresseur()->set_position_x(WINDOW_WIDTH / 2);
	this->_players[0].get_dresseur()->set_position_y(WINDOW_HEIGHT / 2);
	this->_players[0].set_first_on_arene(false);
	this->_placement_covidmon();
	this->_players[0].set_end(false);
	this->_players[0].set_win(false);
}

// On place les dresseurs sur les cases rouges, on a fait
// ca au taton pour les cases.
void Game::_placement_dresseur()
{
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
			it->set_position_y(620.f - SIZE_BLOCK);
			j++;
		}
	}
}

// Placement sur les cases vertes
void Game::_placement_covidmon()
{
	sf::Uint16 i = 1;
	sf::Uint16 j = 1;
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
}

// Initialisation de toutes les variables
void Game::_build()
{
	this->_current_background = intro;
	this->_selec_dresseur = false;
	this->_selec_covidmon = false;
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

	this->_placement_dresseur();
	this->_placement_covidmon();
	sf::Clock c1;
	sf::Clock c2;
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

// Affichage de l'image ou il y a les commandes pour attaquee
void Game::_show_commande()
{
	if(this->_current_background == arene)
	{
		Image att("Images/cmd.png");
		att.set_position_x(60);
		att.set_position_y(WINDOW_HEIGHT - 50);
		att.set_scale(0.28f,0.27f);
		att.draw(this->_window);
	}
}