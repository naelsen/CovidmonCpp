#pragma once

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

#include "define.hh"
#include "Dresseur.hh"
#include "Image.hh"
#include "Player.hh"
#include "Pokemon.hh"

typedef enum Bg
{
	intro,
	menu,
	choix_personnage,
	choix_pokemon,
	arene
} Bg;

typedef std::pair<std::string, Image> couple;

class Game
{
private:
	std::map<std::string, Image> _backgrounds;
	std::vector<Dresseur> _dresseurs;
	std::vector<Pokemon> _pokemons;
	std::vector<Player> _players;

	Bg _current_background;
	bool _selec_dresseur;
	bool _selec_pokemon;
	bool _sound_switched;
	bool _sound_switched2;
	// Attribut SFML
	sf::RenderWindow _window;
	sf::Event _event;
	sf::Clock _clock;
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	sf::SoundBuffer _buffer2;
	sf::Sound _sound2;
	sf::Clock _clock2;
	sf::Font _font;

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
	void _choisir_dresseur();
	void _choisir_pokemon();
	void _draw_pokemon();
	void _switch_sound(std::string);
	void _switch_sound2(std::string);

public:
	Game();
	~Game();
	void run();
};
