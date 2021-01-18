#include "Game.hh"

// IP localhost : 127.0.0.1 (Pareil pour chaque ordi)

// Pour les autres IP si t'es sur Linux tape ca dans ton terminal pour avoir :
// IP local : hostname -I (Je crois que c'est celle la mais jsuis pas sur)
// IP publique : wget http://checkip.dyndns.org/ -O - -o /dev/null | cut -d: -f 2 | cut -d' ' -f 2 | cut -d\< -f 1

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
	    Game game;
	    game.run();
	}

	else if (argc == 2 || argc == 3)
	{
		unsigned int port = atoi(argv[1]);
		if( port < 1024 || port > 65535){
			std::cerr << "Ça va pas non ?"<<std::endl;
		}
		else if(argc == 2)
		{
			Game game(port);
			game.run();
		}
        else
        {
            std::string IP = argv[2];
            std::cout << "Connecté à l'adresse IP : " <<IP<<std::endl;
            Game game(port,IP);
			game.run();
        }
	}
	else
		std::cout<<"Erreur trop d'arguments"<<std::endl;

    return 0;
}