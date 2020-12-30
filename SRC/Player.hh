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
    sf::IpAddress _IP;
    sf::TcpSocket _socket;
    Dresseur *_dresseur;
    std::vector<Covidmon *> _covidmon;
    Image _pokeball;
    int _port;
    bool _accepted;
    bool _first_on_arene;
    bool _end;
    bool _win;

public:
    Player();
    Player(Dresseur &);
    Player(Player const &);
    ~Player();

    int get_port() const;
    bool get_first_on_arene() const;
    bool get_win();
    bool get_end();
    std::vector<Covidmon *> get_covidmon() const;
    Dresseur *get_dresseur() const;

    void set_port(int);
    void set_first_on_arene(bool);
    void set_win(bool);
    void set_end(bool);
    void set_covidmon(Covidmon &);

    bool is_moving();
    void pop_pokeball(sf::RenderWindow &);
    void receive(std::vector<Dresseur> &);
    void receive(std::vector<Covidmon> &, sf::RenderWindow &);
    void send_dresseur();
    void send_covidmon();
    bool is_accepted();
    void disconnect();
};