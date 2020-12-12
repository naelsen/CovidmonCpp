#include "server.hh"

server::server()
{
    if (listener.listen(30000) != sf::Socket::Done)
        std::cout << "Probleme avec le port" << std::endl;
    if (listener.accept(client) != sf::Socket::Done)
        std::cout << "Client pas accépter" << std::endl;
    if (socket.bind(30000) != sf::Socket::Done)
        std::cout << "Client pas accépter" << std::endl;
}

server::~server()
{
}