#include <iostream>
#include <SFML/Network.hpp>
#include <vector>
#include "SRC/Dresseur.hh"

int main()
{
	bool done = false;
	// Permet d'ecouter les connections des clients avec le protocole TCP
	sf::TcpListener listener;
	// Permet de gérer plusieur clients
	sf::SocketSelector selector;

	// Le serveur écoute les entrée du client sur le port 30000
	short int port = 30000;
	if(listener.listen(port) == sf::Socket::Done)
		std::cout << "Server is Ready" << std::endl;
	else
		exit(0);
	
	selector.add(listener);

	// Vecteur de pointeur sur des sockets, chaque socket est associé a un client 
	// Très important pour envoyer et recevoir les informations aux clients
	std::vector<sf::TcpSocket*> Clients;

	while(!done)
	{
		if(selector.wait())
		{
			// Lorsque le listener "entend" une nouvelle arrivée dans le serveur
			if(selector.isReady(listener))
			{
				// On reserve une case pour une socket
				sf::TcpSocket *socket = new sf::TcpSocket();
				listener.accept(*socket);
				selector.add(*socket);
				Clients.push_back(socket);
				sf::Packet receivePacket;
				// Si une nouvelle connexion s'effectue
				if(socket->receive(receivePacket) == sf::Socket::Done)
				{
					std::string nom;
					// On charge le pseudo du joueur dans le paquet
					receivePacket >> nom;
					// On affiche dans le serveur (Mais pas aux joueurs)
					std::cout << "Un joueur viens de se conneccter en choisissant " << nom << std::endl;
				}
			}
			// On gere les autres entrées des clients ici si ya pas de connexion a gerer
			else
			{
				//for(auto it = Clients.begin(); it != Clients.end(); it++)
				for(std::size_t i=0; i < Clients.size(); i++)
				{
					// On regarde si de la donnée est recuperable dans les sockets afin
					// de ne pas attendre pour rien si on recupere on devra attendre une action
					// et ca va bloquer le programme
					if(selector.isReady(*Clients[i]))
					{
						sf::Packet receivePacket;
						// On récupère toute les entrées du client
						if(Clients[i]->receive(receivePacket) == sf::Socket::Done)
						{
							sf::Uint16 x, y;
							int animation;
							int dir;
                            std::string nom;
							// On a charge les informations dans cette ordre avec le client donc on le recupere dans cet ordre
							receivePacket >> nom >> dir >> animation >> x >> y;
							sf::Packet sendPacket;
							sendPacket << nom << dir << animation << x << y;
							// On envoie le paquet a tout les autres clients pour qu'ils savent ce que l'autre client a envoyé au serveur
							for(std::size_t j = 0; j < Clients.size(); j++)
							{
								if(i!=j)
								{
									Clients[j]->send(sendPacket);
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}