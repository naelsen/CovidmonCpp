#pragma once

#include <SFML/Graphics.hpp>

//Dimensions de la fenêtre SFML
static const sf::Uint16 WINDOW_WIDTH = 700; 
static const sf::Uint16 WINDOW_HEIGHT = 700;
//Coordonnées des bords de l'arène
static const sf::Uint16 ARENE_START = 45;
static const sf::Uint16 ARENE_END = 644;
static const sf::Uint16 SIZE_BLOCK = 64;
// Dimensions d'une image mobile
static const sf::Uint16 SIZE_BLOCK_POKEBALL = 16;
// Gestion de la barre de vie 
static const sf::Uint16 LARGEUR_VIE = 131;
static const sf::Uint16 LONGUEUR_VIE = 762;
static const sf::Uint16 NIV_VIE = 150;


/*Type déclarant les différents fonds
 *Element essentiellement utilisé dans Game
 */
typedef enum Bg
{
	intro,
	menu,
	choix_personnage,
	choix_covidmon,
	arene
} Bg;