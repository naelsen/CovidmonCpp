#pragma once

#include "Image.hh"
#include "define.hh"


typedef enum Map
{
	menu,
	personnage,
	pokemon,
	arene
} Map;

class Game
{
private:
	Image menu_game;
	Map map;
	// Attribut SFML
	sf::RenderWindow window;
	sf::Event event;
public:
	Game();
	~Game();
	bool get_map() const;
	void set_map(Map);
	void run();
	void draw();
};