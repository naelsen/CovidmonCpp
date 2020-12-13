#pragma once

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "define.hh"
#include "Dresseur.hh"
#include "Image.hh"
#include "Player.hh"

typedef enum Bg
{
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
	std::vector<Player> _players;

	Bg _current_background;
	bool _selec;
	// Attribut SFML
	sf::RenderWindow _window;
	sf::Event _event;

	bool _get_current_background() const;
	void _set_current_background(Bg);
	void _draw();
	void _draw_bg();
	void _draw_dresseur();
	void _manage();
	void _manage_bg();
	void _manage_dresseur();
	void _choisir_dresseur();
public:
	Game();
	~Game();
	void run();
};