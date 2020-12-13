#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include "Dresseur.hh"

class Player
{
private:
    sf::IpAddress IP;
    sf::TcpSocket socket;
    Dresseur* _dresseur;
    static int numero_joueur;
public:
    Player();
    Player(Dresseur&);
    Player(Player const&);
    ~Player();
    Dresseur* get_dresseur() const;
    void receive(std::vector<Dresseur>&);
    void send();
};