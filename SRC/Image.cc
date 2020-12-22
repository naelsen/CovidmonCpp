#include "Image.hh"

Image::Image()
{
    //std::cout << "Initialisation Image vide à remplacer . . ." << std::endl;
}

Image::Image(std::string nom_image) : __position_x(0),
                                      __position_y(0)
{
    if (!this->__texture_image.loadFromFile(nom_image))
        std::cout << nom_image << " n'a pas été chargé correctement" << std::endl;
    this->__sprite_image.setTexture(this->__texture_image);
    this->__sprite_image.setPosition(sf::Vector2f(this->__position_x, this->__position_y));
}

Image::Image(Image const &im) : __position_x(im.__position_x), __position_y(im.__position_y)
{
    this->__texture_image = im.__texture_image;
    this->__sprite_image.setTexture(this->__texture_image);
    this->__sprite_image.setPosition(sf::Vector2f(this->__position_x, this->__position_y));
}

Image::~Image()
{
}

sf::Uint16 Image::get_position_x() const
{
    return this->__position_x;
}

sf::Uint16 Image::get_position_y() const
{
    return this->__position_y;
}

void Image::set_position_x(sf::Uint16 x)
{
    this->__position_x = x;
}

void Image::set_position_y(sf::Uint16 y)
{
    this->__position_y = y;
}

void Image::draw(sf::RenderWindow &window)
{
    this->__sprite_image.setPosition(this->__position_x, this->__position_y);
    window.draw(this->__sprite_image);
}

float Image::distance(Image const& I)
{
    return sqrt((this->__position_x - I.__position_x)*(this->__position_x - I.__position_x)
                +(this->__position_y - I.__position_y)*(this->__position_y - I.__position_y));
}