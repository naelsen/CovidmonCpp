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
	float __position_x;
	float __position_y;
	// Attributs SFML
	sf::Texture __texture_image;
	sf::Sprite __sprite_image;

public:
	Image();
	Image(std::string);
	Image(Image const&);
	~Image();
	int get_position_x() const;
	int get_position_y() const;
	void set_position_x(float);
	void set_position_y(float);
	void draw(sf::RenderWindow&);
	// On declare la surcharge en friend pour acceder au valeur proteger de la classe
	friend bool operator==(Image const& im1, Image const& im2);

};

// Operateur de comparaison entre image pour les collisions
inline bool operator==(Image const& im1, Image const& im2)
{
	float dx = im1.__position_x - im2.__position_x;
	float dy = im1.__position_y - im2.__position_y;
	bool collision_x = dx*dx < (SIZE_HEIGHT_DRESSEUR/2.f)*(SIZE_HEIGHT_DRESSEUR/2.f);
	bool collision_y = dy*dy < (SIZE_HEIGHT_DRESSEUR/2.f)*(SIZE_HEIGHT_DRESSEUR/2.f);
	if(collision_x && collision_y)
		return true;
    else
	    return false;
}