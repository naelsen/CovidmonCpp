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
    sf::Uint16 x, y, animation;
    sf::TcpListener _listener;
    sf::SocketSelector _selector;
    std::vector<sf::TcpSocket *> _Clients;
    std::vector<std::string> _nom_clients;

public:
    Serveur();
    ~Serveur();

    void run();
    void accept_client();
    void action_clients();
};
