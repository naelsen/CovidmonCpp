#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <string>

#include "Dresseur.hh"
#include "Image.hh"
#include "Pokemon.hh"

class Player
{
private:
    sf::IpAddress IP;
    sf::TcpSocket socket;
    Dresseur *_dresseur;
    Pokemon *_pokemon;
    Image _pokeball;
    static int numero_joueur;
    bool _accepted;
    bool _first_on_arene;

public:
    Player();
    Player(Dresseur &);
    Player(Player const &);
    ~Player();
    void set_pokemon(Pokemon &);
    Dresseur *get_dresseur() const;
    Pokemon *get_pokemon() const;
    bool get_first_on_arene() const;
    void pop_pokeball(sf::RenderWindow &);
    void receive(std::vector<Dresseur> &);
    void receive(std::vector<Pokemon> &);
    bool is_moving();
    void send();
    void send_pokemon();
    bool is_accepted();
    void disconnect();
};