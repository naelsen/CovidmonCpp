#include "Player.hh"
#include <SFML/Graphics.hpp>

Player::Player()
{
}

Player::Player(Dresseur &dresseur) : _dresseur(&dresseur),
                                     _pokeball("Images/pokeball.png"),
                                     _port(30001),
                                     _accepted(true),
                                     _first_on_arene(true),
                                     _end(false),
                                     _win(false)
{
    this->_IP = sf::IpAddress::getLocalAddress();
}

Player::Player(Dresseur &dresseur, unsigned int port) : _dresseur(&dresseur),
                                                     _pokeball("Images/pokeball.png"),
                                                     _port(port),
                                                     _accepted(true),
                                                     _first_on_arene(true),
                                                      _end(false),
                                                     _win(false)
{
    this->_IP = sf::IpAddress::getLocalAddress();
}

Player::Player(Dresseur &dresseur, unsigned int port,std::string ip) : _dresseur(&dresseur),
                                                                  _pokeball("Images/pokeball.png"),
                                                                  _port(port),
                                                                  _accepted(true),
                                                                  _first_on_arene(true),
                                                                  _end(false),
                                                                  _win(false)
{
    this->_IP = ip;
}

Player::Player(Player const &P) : _IP(P._IP),
                                  _dresseur(P._dresseur),
                                  _pokeball(P._pokeball),
                                  _port(P._port),
                                  _accepted(P._accepted),
                                  _first_on_arene(P._first_on_arene),
                                  _end(P._end),
                                  _win(P._win)
{
    // Le client se connecte au port avec son IP a condition que le serveur ai deja été lancé
    if (this->_socket.connect(_IP, _port) == sf::Socket::Done)
    {
        std::cout << "Tentative de connexion au serveur..." << std::endl;
        sf::Packet sendPacket;
        // On charge le pseudo dans le paquet a envoyer au serveur
        sendPacket << this->get_dresseur()->get_nom();
        // On envoie
        this->_socket.send(sendPacket);
        sf::Packet receivePacket;
        // Le joueur a t il ete accepter par le serveur ?
        if (this->_socket.receive(receivePacket) == sf::Socket::Done)
            receivePacket >> this->_accepted;
        // Non
        if (!this->_accepted)
        {
            std::cout << "Deconnecte du serveur car soit : " << std::endl;
            std::cout << "Un joueur possède déjà ce personage" << std::endl;
            std::cout << "Déja 2 personnes sont connéctés" << std::endl;
            this->_socket.disconnect();
            this->_accepted = false;
        }
        // Oui
        else
        {
            std::cout << "Connexion reussi" << std::endl;
        }
    }
    else
    {
        std::cout << "Serveur pas encore crée, lancez le dans un autre terminal !" << std::endl;
        exit(0);
    }
    // Afin de ne pas bloquer le programme quand on attend une socket
    this->_socket.setBlocking(false);
}

Player::~Player()
{
}

int Player::get_port() const
{
    return this->_port;
}

bool Player::get_first_on_arene() const
{
    return this->_first_on_arene;
}

bool Player::get_win()
{
    if (!this->_covidmon[0]->get_est_vivant() || !this->_covidmon[1]->get_est_vivant())
    {
        if (this->_covidmon[0]->get_est_vivant())
            this->_win = true;
    }
    return this->_win;
}

bool Player::get_end()
{
    if (this->get_covidmon().size() == 2)
    {
        if (!this->_covidmon[0]->get_est_vivant() || !this->_covidmon[1]->get_est_vivant())
            this->_end = true;
    }
    return this->_end;
}

std::vector<Covidmon *> Player::get_covidmon() const
{
    return this->_covidmon;
}

Dresseur *Player::get_dresseur() const
{
    return this->_dresseur;
}

void Player::set_port(int p)
{
    this->_port = p;
}

void Player::set_first_on_arene(bool first)
{
    this->_first_on_arene = first;
}

void Player::set_win(bool win)
{
    this->_win = win;
}

void Player::set_end(bool end)
{
    this->_end = end;
}

void Player::set_covidmon(Covidmon &pok)
{
    this->_covidmon.push_back(&pok);
}

bool Player::is_moving()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return true;

    return false;
}

// Permet de placer la pokeball quand le joueur a choisi son pokemon
void Player::pop_pokeball(sf::RenderWindow &window)
{
    this->_pokeball.set_position_x(this->_dresseur->get_position_x() + SIZE_BLOCK / 2 - SIZE_BLOCK_POKEBALL / 2);
    this->_pokeball.set_position_y(this->_dresseur->get_position_y() - SIZE_BLOCK_POKEBALL / 2);
    this->_pokeball.draw(window);
}

// Sert a recevoir les données du joueur adverse qui contre un des dresseurs
void Player::receive(std::vector<Dresseur> &dresseurs)
{
    sf::Packet receivePacket;
    if (this->_socket.receive(receivePacket) == sf::Socket::Done)
    {
        sf::Uint16 x, y, animation;
        int dir, bg;
        Direction d;
        std::string nom;
        Bg current_bg;

        // On charge les variables
        receivePacket >> nom >> dir >> animation >> x >> y >> bg;

        // On converti en Direction
        if (dir == 0)
            d = Down;
        if (dir == 1)
            d = Left;
        if (dir == 2)
            d = Right;
        if (dir == 3)
            d = Up;

        // On converti en Bg
        if (bg == 0)
            current_bg = intro;
        if (bg == 1)
            current_bg = menu;
        if (bg == 2)
            current_bg = choix_personnage;
        if (bg == 3)
            current_bg = choix_covidmon;
        if (bg == 4)
            current_bg = arene;

        // Si un joueur est déja la alors il n'est pas premier dans l'arene (Ca servira pour les placement a droite et a gauche)
        if (current_bg == arene && this->get_dresseur()->get_current_bg() != arene && this->_first_on_arene)
        {
            this->_first_on_arene = false;
        }

        // On met a jour les informations indispensable du joueur adverse
        for (auto it = dresseurs.begin(); it != dresseurs.end(); it++)
        {
            if (it->get_nom() == nom)
            {
                it->set_position_x(x);
                it->set_position_y(y);
                it->set_direction(d);
                it->set_animation(animation);
                it->set_current_bg(current_bg);
            }
        }
    }
}

// Sert a recevoir les données du joueur adverse qui contre un des Covidmon
void Player::receive(std::vector<Covidmon> &Covidmon, sf::RenderWindow &window)
{
    sf::Packet receivePacket;
    if (this->_socket.receive(receivePacket) == sf::Socket::Done)
    {
        sf::Uint16 x, y, animation, pv_current;
        int dir, bg;
        bool is_attacking_near;
        bool is_attacking_far;
        Direction d;
        std::string nom;
        Bg current_bg;

        // On charge les variables
        receivePacket >> nom >> dir >> animation >> x >> y >> bg >> pv_current >> is_attacking_near >> is_attacking_far;

        bool push = true;
        for (std::size_t it = 0; it < _covidmon.size(); it++)
        {
            if (_covidmon[it]->get_nom() == nom)
                push = false;
        }
        // Si aucun pokemon n'appartient a vector
        if (push)
        {
            for (auto it = Covidmon.begin(); it != Covidmon.end(); it++)
            {
                if (it->get_nom() == nom)
                {
                    std::cout << nom << " push" << std::endl;
                    this->set_covidmon(*it);
                }
            }
        }

        if (this->_covidmon.size() == 2)
        {
            // Le covidmon attaque t il de loin?
            if (is_attacking_far && !this->_covidmon[1]->get_attaque_de_loin().get_est_lancee())
            {
                // Le pokemon attaque de loin
                this->_covidmon[1]->get_attaque_de_loin().set_est_lancee(is_attacking_far);
                this->_covidmon[1]->get_attaque_de_loin().set_just_clicked(true);
            }
            // Le covidmon attaque t il de pres?
            if (is_attacking_near && !this->_covidmon[1]->get_attaque_de_pres().get_est_lancee())
            {
                // Le pokemon attaque de pres
                this->_covidmon[1]->get_attaque_de_pres().set_est_lancee(is_attacking_near);
                this->_covidmon[1]->get_attaque_de_pres().set_just_clicked(true);
            }
        }

        // On converti en Direction
        if (dir == 0)
            d = Down;
        if (dir == 1)
            d = Left;
        if (dir == 2)
            d = Right;
        if (dir == 3)
            d = Up;

        // On converti en Bg
        if (bg == 0)
            current_bg = intro;
        if (bg == 1)
            current_bg = menu;
        if (bg == 2)
            current_bg = choix_personnage;
        if (bg == 3)
            current_bg = choix_covidmon;
        if (bg == 4)
            current_bg = arene;

        // On met a jour les informations indispensable du covidmon adverse
        // qui vont aussi servir a mettre a jour via des fonctions d'autre attributs.
        for (auto it = Covidmon.begin(); it != Covidmon.end(); it++)
        {
            if (it->get_nom() == nom)
            {
                it->set_position_x(x);
                it->set_position_y(y);
                it->set_direction(d);
                it->set_animation(animation);
                it->set_current_bg(current_bg);
                it->set_pv_current(pv_current);
            }
        }
    }
}

void Player::send_dresseur()
{
    sf::Packet sendPacket_type;
    sf::Packet sendPacket_data;
    // Chargement des paquets a envoyer au serveur
    sendPacket_type << "dresseur";
    sendPacket_data << this->_dresseur->get_nom()
                    << this->_dresseur->get_direction()
                    << this->get_dresseur()->get_animation()
                    << this->_dresseur->get_position_x()
                    << this->_dresseur->get_position_y()
                    << this->_dresseur->get_current_bg();
    // Envoie des paquets
    this->_socket.send(sendPacket_type);
    this->_socket.send(sendPacket_data);
}

void Player::send_covidmon()
{
    sf::Packet sendPacket_type;
    sf::Packet sendPacket_data;
    // Chargement des paquets a envoyer au serveur
    sendPacket_type << "covidmon";
    sendPacket_data << this->_covidmon[0]->get_nom()
                    << this->_covidmon[0]->get_direction() << this->get_covidmon()[0]->get_animation()
                    << this->_covidmon[0]->get_position_x() << this->_covidmon[0]->get_position_y()
                    << this->_covidmon[0]->get_current_bg() << this->_covidmon[0]->get_pv_current()
                    << this->_covidmon[0]->get_attaque_de_pres().get_est_lancee()
                    << this->_covidmon[0]->get_attaque_de_loin().get_est_lancee();
    // Envoie des paquets
    this->_socket.send(sendPacket_type);
    this->_socket.send(sendPacket_data);
}

bool Player::is_accepted()
{
    return this->_accepted;
}

void Player::disconnect()
{
    this->_socket.disconnect();
    std::cout << "Deconnexion du serveur !" << std::endl;
}