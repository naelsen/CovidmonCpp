#include <iostream>
#include <SFML/Network.hpp>
#include <vector>

#include "Dresseur.hh"

class Serveur
{
private:
    short int _port;
	bool _done;
    sf::TcpListener _listener;
	sf::SocketSelector _selector;
    std::vector<sf::TcpSocket *> _Clients;
public:
    Serveur();
    ~Serveur();

    void run();
    void accept_client();
    void action_clients();
};
