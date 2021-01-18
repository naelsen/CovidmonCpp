#include "Serveur.hh"

Serveur::Serveur() : _port(30001),
                     _done(false)
{
    // On prépare le serveur a ecouté sur le port 30001
    if (this->_listener.listen(this->_port) == sf::Socket::Done)
        std::cout << "Server is Ready in the port : " << this->_port << std::endl;
    else
        exit(0);

    // Important de rajouter aux selecteur l'ecouteur, sinon le selecteur ne peut pas attendre
    this->_selector.add(this->_listener);

    // =======
    std::cout << "Nombre joueurs connectés: " << this->_nom_clients.size() << std::endl;
}

Serveur::Serveur(unsigned int port) : _port(port),
                     _done(false)
{
    // On prépare le serveur a ecouté sur le port donné en parametre
    if (this->_listener.listen(this->_port) == sf::Socket::Done)
        std::cout << "Server is Ready in the port : " << this->_port << std::endl;
    else
        exit(0);
    // Important de rajouter aux selecteur l'ecouteur, sinon le selecteur ne peut pas attendre
    this->_selector.add(this->_listener);

    // =======
    std::cout << "Nombre joueurs connectés: " << this->_nom_clients.size() << std::endl;
}

Serveur::~Serveur()
{
}

unsigned int Serveur::get_port() const
{
    return this->_port;
}

void Serveur::set_port(unsigned int p)
{
    this->_port = p;
}

void Serveur::run()
{
    // Boucle principale du serveur
    while (!this->_done)
    {
        if (this->_selector.wait())
        {
            // Si le selecteur est pret concernant l'ecouteur, on accepte le client
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
    // On l'accepte
    this->_listener.accept(*socket);
    // Ajout au selecteur
    this->_selector.add(*socket);
    // On accepte temporairement un joueur
    this->_Clients.push_back(socket);
    // On prépare un paquet (Qui est temporaire) pour recevoir le nom du personnage que le
    // Client a choisi
    sf::Packet receivePacket;
    bool accepted = true;
    // Si regarde si un paquet est pret a etre chargé
    if (socket->receive(receivePacket) == sf::Socket::Done)
    {
        // On charge le pseudo du joueur choisi par le Client dans le paquet
        receivePacket >> this->_nom;
        // On verifie si le joueur a déja été choisi
        if (this->_nom_clients.size() == 1)
        {
            for (std::size_t i = 0; i < _nom_clients.size(); i++)
            {
                // Si déjà un client possède ce dresseur alors le client 
                // qui à été accepter temporairement sera enlever du serveur
                if (this->_nom_clients[i] == this->_nom)
                {
                    accepted = false;
                }
            }
        }
        // Si déjà deux client sont dans le serveur on va enlever du serveur le client 
        // qui à été accepter temporairement
        else if (this->_nom_clients.size() > 1)
            accepted = false;
        
        // On prépare un paquet pour lui informer au joueur si il a été accépter dans le serveur
        sf::Packet sendPacket;
        sendPacket << accepted;

        // On l'envoie
        this->_Clients[this->_nom_clients.size()]->send(sendPacket);

        // On ajoute le nom du dresseur choisi par le nouveau client (qui n'est plus temporaire du coup)
        if (accepted)
        {
            this->_nom_clients.push_back(this->_nom);
            std::cout << "Un joueur viens de se connecter en choisissant " << this->_nom << std::endl;
        }
        // On supprime le client du serveur
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
        // La socket est elle prête a recevoir des information ????
        if (this->_selector.isReady(*this->_Clients[i]))
        {
            this->communication_dresseur(i);
            this->communication_covidmon(i);
        }
    }
}

void Serveur::communication_dresseur(std::size_t i)
{
    // Paquet qui va servir a savoir si le données concerne le dresseur ou le covidmon
    sf::Packet receivePacket_type;
    // Les infos recues
    sf::Packet receivePacket_data;
    // Si une paquet est recu on entre dans le if
    if (this->_Clients[i]->receive(receivePacket_type) == sf::Socket::Done)
    {
        this->_Clients[i]->receive(receivePacket_data);
        receivePacket_type >> this->_type;
        if (this->_type == "dresseur")
        {
            // On a chargé les informations dans cette ordre avec le client donc on le recupere dans cet ordre
            receivePacket_data >> this->_nom >> this->_dir >> this->_animation >> this->_x >> this->_y >> this->_bg;
            sf::Packet sendPacket;
            sendPacket << this->_nom << this->_dir << this->_animation << this->_x << this->_y << this->_bg;
            // On envoie le paquet au client qui n'a pas envoyer le paquet
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

// Meme fonctionnement que précedemment
void Serveur::communication_covidmon(std::size_t i)
{
    sf::Packet receivePacket_type;
    sf::Packet receivePacket_data;
    if (this->_Clients[i]->receive(receivePacket_type) == sf::Socket::Done)
    {
        this->_Clients[i]->receive(receivePacket_data);
        receivePacket_type >> this->_type;
        if (this->_type == "covidmon")
        {
            receivePacket_data >> this->_nom >> this->_dir >> this->_animation >> this->_x >> this->_y >> this->_bg >> this->_pv_current >> this->_is_attacking_near >> this->_is_attacking_far;
            if (this->_nom_covidmon.size() == 0)
            {
                this->_nom_covidmon.push_back(this->_nom);
                std::cout << this->_nom << " est pret a combattre" << std::endl;
            }
            else if (this->_nom_covidmon.size() == 1)
            {
                bool accepted = true;
                for (std::size_t j = 0; j < this->_nom_covidmon.size(); j++)
                {
                    if (this->_nom_covidmon[j] == this->_nom)
                    {
                        accepted = false;
                    }
                }
                if (accepted)
                {
                    this->_nom_covidmon.push_back(this->_nom);
                    std::cout << this->_nom << " est pret a combattre" << std::endl;
                }
            }
            sf::Packet sendPacket;
            sendPacket << this->_nom << this->_dir << this->_animation << this->_x << this->_y << this->_bg << this->_pv_current << this->_is_attacking_near << this->_is_attacking_far;
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