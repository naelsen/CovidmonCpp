#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class Image
{
private:
	float position_x;
	float position_y;
	// Attributs SFML
	sf::Texture texture_image;
	sf::Sprite sprite_image;

public:
	Image(std::string);
	~Image();
	void draw(sf::RenderWindow&);
};
