#include "Serveur.hpp"

Serveur::Serveur() : _port(30001),
                     _done(false)
{
    if (this->_listener.listen(_port) == sf::Socket::Done)
        std::cout << "Server is Ready" << std::endl;
    else
        exit(0);
    this->_selector.add(this->_listener);
    std::cout << "Nombre joueurs connectés: " << this->_nom_clients.size() << std::endl;
}

Serveur::~Serveur()
{
}

void Serveur::run()
{
    while (!this->_done)
    {
        if (this->_selector.wait())
        {
            if (this->_selector.isReady(this->_listener))
            {
                this->accept_client();
            }
            else
            {
                this->action_clients();
            }
        }
    }
}

void Serveur::accept_client()
{
    // On reserve une case pour une socket
    sf::TcpSocket *socket = new sf::TcpSocket();
    this->_listener.accept(*socket);
    this->_selector.add(*socket);
    this->_Clients.push_back(socket);
    sf::Packet receivePacket;
    bool accepted = true;
    // Si une nouvelle connexion s'effectue

    if (socket->receive(receivePacket) == sf::Socket::Done)
    {
        std::string nom;
        // On charge le pseudo du joueur dans le paquet
        receivePacket >> nom;
        if (this->_nom_clients.size() == 1)
        {
            for (std::size_t i = 0; i < _nom_clients.size(); i++)
            {
                if (this->_nom_clients[i] == nom)
                {
                    accepted = false;
                }
            }
        }
        else if(this->_nom_clients.size() > 1)
            accepted = false;
        // On affiche dans le serveur (Mais pas aux joueurs)
        sf::Packet sendPacket;
        sendPacket << accepted;
        // On informe au client qui essaye de se connecter si il est accepter
        // Il sera accepter si le joueur choisis n'a pas encore ete choisi par quelqu'un d'autre
        this->_Clients[this->_nom_clients.size()]->send(sendPacket);

        if (accepted)
        {
            this->_nom_clients.push_back(nom);
            std::cout << "Un joueur viens de se connecter en choisissant " << nom << std::endl;
        }
        else
        {
            std::cout << "Joueur refoulé du serveur" << std::endl;
            this->_Clients.pop_back();
        }
        std::cout << "Nombre joueurs connectés: " << this->_nom_clients.size() << std::endl;
    }
}

void Serveur::action_clients()
{
    for (std::size_t i = 0; i < this->_Clients.size(); i++)
    {
        // On regarde si de la donnée est recuperable dans les sockets afin
        // de ne pas attendre pour rien si on recupere on devra attendre une action
        // et ca va bloquer le programme
        if (this->_selector.isReady(*this->_Clients[i]))
        {
            communication_dresseur(i);
            communication_covidmon(i);
        }
    }
}

void Serveur::communication_dresseur(std::size_t i)
{
    sf::Packet receivePacket_type;
    sf::Packet receivePacket_data;
    // On récupère toute les entrées du client
    if (this->_Clients[i]->receive(receivePacket_type) == sf::Socket::Done)
    {
        this->_Clients[i]->receive(receivePacket_data);
        std::string type;
        receivePacket_type >> type;
        if(type == "dresseur")
        {
            int dir, bg;
            std::string nom;
            // On a charge les informations dans cette ordre avec le client donc on le recupere dans cet ordre
            receivePacket_data >> nom >> dir >> animation >> x >> y >> bg;
            sf::Packet sendPacket;
            sendPacket << nom << dir << animation << x << y << bg;
            // On envoie le paquet a tout les autres clients pour qu'ils savent ce que l'autre client a envoyé au serveur
            for (std::size_t j = 0; j < this->_Clients.size(); j++)
            {
                if (i != j)
                {
                    this->_Clients[j]->send(sendPacket);
                }
            }
        }
    }
}

void Serveur::communication_covidmon(std::size_t i)
{
    sf::Packet receivePacket_type;
    sf::Packet receivePacket_data;
    // On récupère toute les entrées du client
    if (this->_Clients[i]->receive(receivePacket_type) == sf::Socket::Done)
    {
        this->_Clients[i]->receive(receivePacket_data);
        std::string type;
        receivePacket_type >> type;
        if(type == "covidmon")
        {
            int dir, bg;
            std::string nom;
            bool is_attacking_near;
            bool is_attacking_far;
            // On a charge les informations dans cette ordre avec le client donc on le recupere dans cet ordre
            receivePacket_data >> nom >> dir >> animation >> x >> y >> bg >> pv_current >> is_attacking_near >> is_attacking_far ;
            if(_nom_covidmon.size() == 0)
            {
                _nom_covidmon.push_back(nom);
                std::cout << nom << " est pret a combattre" << std::endl;
            }
            else if(_nom_covidmon.size() == 1)
            {
                bool accepted = true;
                for (std::size_t j = 0; j < _nom_covidmon.size(); j++)
                {
                    if (this->_nom_covidmon[j] == nom)
                    {
                        accepted = false;
                    }
                }
                if(accepted)
                {
                    _nom_covidmon.push_back(nom);
                    std::cout << nom << " est pret a combattre" << std::endl;
                }
            }
            sf::Packet sendPacket;
            sendPacket << nom << dir << animation << x << y << bg << pv_current << is_attacking_near << is_attacking_far;
            // On envoie le paquet a tout les autres clients pour qu'ils savent ce que l'autre client a envoyé au serveur
            for (std::size_t j = 0; j < this->_Clients.size(); j++)
            {
                if (i != j)
                {
                    this->_Clients[j]->send(sendPacket);
                }
            }
        }
    }
}