#include "Image.hh"

Image::Image(std::string nom_image): position_x(0), position_y(0)
{
	if (!this->texture_image.loadFromFile(nom_image))
        std::cout << "Le menu n'a pas été chargé correctement" << std::endl;
    this->sprite_image.setTexture(this->texture_image);
    this->sprite_image.setPosition(sf::Vector2f(this->position_x,this->position_y));
}

Image::~Image()
{
}

void Image::draw(sf::RenderWindow &window)
{
	window.draw(this->sprite_image);
}