#include "Player.hh"
#include <SFML/Graphics.hpp>

Player::Player()
{
}

Player::Player(Dresseur& dresseur) : _dresseur(&dresseur), _pokeball("Images/pokeball.png")
{
    this->IP = sf::IpAddress::getLocalAddress();
}

Player::Player(Player const& P):
IP(P.IP),
_dresseur(P._dresseur),
_pokeball(P._pokeball)
{
    short int port = 30000;
    // Le client se connecte au port avec son IP a condition que le serveur ai deja été lancé
    if(this->socket.connect(IP,port) == sf::Socket::Done)
    {
        std::cout << "Connecte au serveur !" << std::endl;
        sf::Packet sendPacket;
        // On charge le pseudo dans le paquet a envoyer au serveur
        sendPacket << this->get_dresseur()->get_nom();
        // On envoie
        socket.send(sendPacket);
    }
    else
    {
        std::cout << "Serveur pas encore crée, lancez le dans un autre terminal !" << std::endl;
        exit(0);
    }
    // Afin de ne pas bloquer le programme quand on attend une socket
    this->socket.setBlocking(false);
}

Player::~Player()
{
}
// Fonction ajoutée pour le bruit des pas
// elle evite de faire les 4 conditions a chaque fois
bool Player::is_moving()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		return true;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return true;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		return true;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return true;
	
	return false;
}

void Player::set_pokemon(Pokemon& pok)
{
    this->_pokemon = &pok;
}

Dresseur* Player::get_dresseur() const
{
    return this->_dresseur;
}

Pokemon* Player::get_pokemon() const
{
    return this->_pokemon;
}

void Player::pop_pokeball(sf::RenderWindow& window)
{
    this->_pokeball.set_position_x(this->_dresseur->get_position_x()+SIZE_WIDTH_PERSO/2 - SIZE_BLOCK_POKEBALL/2);
    this->_pokeball.set_position_y(this->_dresseur->get_position_y()-SIZE_BLOCK_POKEBALL/2);
    this->_pokeball.draw(window);
}

void Player::receive(std::vector<Dresseur>& dresseurs)
{
    sf::Packet receivePacket;
    if(socket.receive(receivePacket) == sf::Socket::Done)
    {
        sf::Uint16 x,y;
        int animation;
        int dir;
        Direction d;
        std::string nom;
		receivePacket >> nom >> dir >> animation >> x >> y;
        if(dir == 0)
            d = Down;
        if(dir == 1)
            d = Left;
        if(dir == 2)
            d = Right;
        if(dir == 3)
            d = Up;
        for(auto it = dresseurs.begin(); it != dresseurs.end(); it++)
        {
            if(it->get_nom() == nom)
            {
		        it->set_position_x(x);
		        it->set_position_y(y);
                it->set_direction(d);
                it->set_animation(animation);
            }
        }
    }  
}

void Player::send()
{
    sf::Packet sendPacket;
    sendPacket << this->_dresseur->get_nom() << this->_dresseur->get_direction() <<  this->get_dresseur()->get_animation() << this->_dresseur->get_position_x() << this->_dresseur->get_position_y();
    socket.send(sendPacket);
}


/*sf::Packet& operator <<(sf::Packet& packet, Direction dir)
{
    return packet << dir
}
*/
/*sf::Packet& operator <<(sf::Packet& packet, const Player& P)
{
    return packet << P.get_dresseur()->get_nom() << P.get_dresseur()->get_position_x() << P.get_dresseur()->get_position_y();
}

sf::Packet& operator >>(sf::Packet& packet, Player& P)
{
    return packet >> P.get_dresseur()->get_nom() >> P.get_dresseur()->get_position_x() >> P.get_dresseur()->get_position_y();
}*/