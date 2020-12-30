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
	// Clock i sert a gerer le temps du son i dans les conditions de game
	std::vector<sf::Clock> _clocks;
	// Buffer i correspond au son i
	sf::Music _sound_front;
	sf::Music _sound_back;
	// Sert à gerer les differents sons des backgrounds
	std::vector<bool> _sounds_switched;
	Bg _current_background;
	bool _selec_dresseur;
	bool _selec_covidmon;
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
	void _manage();
	void _manage_sound();
	void _front_sound();
	void _back_sound();
	void _manage_bg();
	void _manage_dresseur();
	void _manage_covidmon();
	void _choisir_dresseur();
	void _choisir_covidmon();
	void _draw_covidmon();
	void _switch_sound(std::size_t, std::string);
	void check_end();
	void clean();
	void placement_dresseur();
	void placement_covidmon();

public:
	Game();
	~Game();
	void run();
};
