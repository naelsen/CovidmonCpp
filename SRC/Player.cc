#include "Player.hh"

Player::Player(std::string image) : Dresseur(image)
{
    // On récupere l'adresse IP internet de celui qui lance le programme
	char IP_bis[40];
	FILE *f = popen("wget http://checkip.dyndns.org/ -O - -o /dev/null | cut -d: -f 2 | cut -d' ' -f 2 | cut -d\\< -f 1", "r");
	if (!f) { perror("popen"); exit(1); };
	fscanf(f, " %s", IP_bis);
	pclose(f);
	// On transforme en string pour que ca soit plus jolie
	this->IP = IP_bis;
    // On se connect au port 30000 avec l'adresse IP du player
    this->status = socket.bind(30000,IP);
    if (this->status != sf::Socket::Done)
    {
        std::cout << "Erreur Soket" << std::endl;
        std::cout << "IP : " << IP << std::endl;
        std::cout << "Serveur : " << 30000 << std::endl;
    }
}

Player::~Player()
{
}
