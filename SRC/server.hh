#include <iostream>
#include <SFML/Network.hpp>
#include <string>

class server
{
private:
    sf::TcpListener listener;
    sf::TcpSocket client;
    sf::UdpSocket socket;
public:
    server();
    ~server();
    void send_data(std::string);
    void receive_data();
};
