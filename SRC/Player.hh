#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <string>

#include "Dresseur.hh"

class Player : public Dresseur
{
private:
    sf::UdpSocket socket;
    sf::Socket::Status status;
    sf::IpAddress IP;
public:
    Player(std::string);
    ~Player();
};