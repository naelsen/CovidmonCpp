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
    std::vector<Covidmon*> _covidmon;
    Image _pokeball;
    static int numero_joueur;
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
    void set_covidmon(Covidmon &);
    Dresseur *get_dresseur() const;
    std::vector<Covidmon*> get_covidmon() const;
    int get_port()const;
    //Covidmon *get_nom_covidmon_adverse() const;
    bool get_first_on_arene() const;
    bool get_win();
    bool get_end();
    void set_win(bool);
    void set_end(bool);
    void set_first_on_arene(bool);
    void set_port(int);
    void pop_pokeball(sf::RenderWindow &);
    void receive(std::vector<Dresseur> &);
    void receive(std::vector<Covidmon> &, sf::RenderWindow&);
    bool is_moving();
    void send();
    void send_covidmon();
    void send_attaque_pres();
    void send_attaque_loin();
    void send_win();
    bool is_accepted();
    void disconnect();
};