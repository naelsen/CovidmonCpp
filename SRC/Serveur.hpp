#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <vector>

#include "Dresseur.hh"

class Serveur
{
private:
    short int _port;
    bool _done;
    bool is_attacking_near;
    bool is_attacking_far;
    sf::Uint16 x, y, animation, pv_current;
    sf::TcpListener _listener;
    sf::SocketSelector _selector;
    std::vector<sf::TcpSocket *> _Clients;
    std::vector<std::string> _nom_clients;
    std::vector<std::string> _nom_covidmon;

public:
    Serveur();
    ~Serveur();
    short int get_port() const;
    void set_port(short int p );
    void run();
    void accept_client();
    void action_clients();
    void communication_dresseur(std::size_t);
    void communication_covidmon(std::size_t);
};
