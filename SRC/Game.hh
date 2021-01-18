#pragma once

#include <iostream>
#include <list>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

#include "define.hh"
#include "Dresseur.hh"
#include "Image.hh"
#include "Player.hh"
#include "Covidmon.hh"
#include "Attaque_de_loin.hh"
#include "Attaque_de_pres.hh"

typedef std::pair<std::string, Image> couple;

class Game
{
private:
	std::map<std::string, Image> _backgrounds;
	std::vector<Dresseur> _dresseurs;
	std::vector<Covidmon> _covidmons;
	std::vector<Player> _players;
	std::vector<sf::Clock> _clocks;
	sf::Music _sound_front;
	sf::Music _sound_back;
	std::vector<bool> _sounds_switched;
	Bg _current_background;
	bool _selec_dresseur;
	bool _selec_covidmon;
	short int _port;
	std::string _IP;
	// Attribut SFML
	sf::RenderWindow _window;
	sf::Event _event;

	sf::Font _font;
	sf::Text _text;

	Bg _get_current_background() const;
	void _set_current_background(Bg);
	void _draw();
	void _draw_bg();
	void _draw_dresseur();
	void _draw_covidmon();
	void _back_sound();
	void _play_front(std::string fichier);
	void _front_sound();
	void _manage();
	void _manage_sound();
	void _manage_bg();
	void _manage_dresseur();
	void _manage_covidmon();
	void _choisir_dresseur();
	void _choisir_covidmon();
	void _check_end();
	void _clean();
	void _placement_dresseur();
	void _placement_covidmon();
	void _build();
	void _show_commande();

public:
	Game();
	Game(unsigned int);
	Game(unsigned int, std::string);
	~Game();
	void run();
};
