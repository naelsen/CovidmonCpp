#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <vector>

#include "Dresseur.hh"

class Serveur
{
private:
    int _dir, _bg;
    short int _port;
    bool _done;
    bool _is_attacking_near;
    bool _is_attacking_far;
    std::string _nom;
    std::string _type;
    sf::Uint16 _x, _y, _animation, _pv_current;
    sf::TcpListener _listener;
    sf::SocketSelector _selector;
    std::vector<sf::TcpSocket *> _Clients;
    std::vector<std::string> _nom_clients;
    std::vector<std::string> _nom_covidmon;
    void communication_dresseur(std::size_t);
    void communication_covidmon(std::size_t);

public:
    Serveur();
    ~Serveur();
    short int get_port() const;
    void set_port(short int p);
    void run();
    void accept_client();
    void action_clients();
};
