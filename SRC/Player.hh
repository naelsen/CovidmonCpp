#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <string>

#include "Dresseur.hh"
#include "Image.hh"
#include "Covidmon.hh"

class Player
{
private:
    sf::IpAddress IP;
    sf::TcpSocket socket;
    Dresseur *_dresseur;
    Covidmon *_covidmon;
    Image _pokeball;
    static int numero_joueur;
    bool _accepted;
    bool _first_on_arene;

public:
    Player();
    Player(Dresseur &);
    Player(Player const &);
    ~Player();
    void set_covidmon(Covidmon &);
    Dresseur *get_dresseur() const;
    Covidmon *get_covidmon() const;
    bool get_first_on_arene() const;
    void pop_pokeball(sf::RenderWindow &);
    void receive(std::vector<Dresseur> &);
    void receive(std::vector<Covidmon> &, sf::RenderWindow&);
    bool is_moving();
    void send();
    void send_covidmon();
    void send_attaque_pres();
    void send_attaque_loin();
    bool is_accepted();
    void disconnect();
};