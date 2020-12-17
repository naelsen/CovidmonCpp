#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "define.hh"

typedef enum Direction
{
	Down,
	Left,
	Right,
	Up
} Direction;

class Image
{
protected:
	sf::Uint16 __position_x;
	sf::Uint16 __position_y;
	// Attributs SFML
	sf::Texture __texture_image;
	sf::Sprite __sprite_image;

public:
	Image();
	Image(std::string);
	Image(Image const&);
	~Image();
	sf::Uint16 get_position_x() const;
	sf::Uint16 get_position_y() const;
	void set_position_x(sf::Uint16);
	void set_position_y(sf::Uint16);
	void draw(sf::RenderWindow&);
	// On declare la surcharge en friend pour acceder au valeur proteger de la classe
	friend bool operator==(Image const& im1, Image const& im2);

};

// Operateur de comparaison entre image pour les collisions
inline bool operator==(Image const& im1, Image const& im2)
{
	sf::Uint16 dx = im1.__position_x - im2.__position_x;
	sf::Uint16 dy = im1.__position_y - im2.__position_y;
	bool collision_x = dx*dx < (SIZE_HEIGHT_PERSO/2)*(SIZE_HEIGHT_PERSO/2);
	bool collision_y = dy*dy < (SIZE_HEIGHT_PERSO/2)*(SIZE_HEIGHT_PERSO/2);
	if(collision_x && collision_y)
		return true;
    else
	    return false;
}