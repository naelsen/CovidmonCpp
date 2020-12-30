#include <iostream>

#include "Serveur.hh"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
	    Serveur serveur;
	    serveur.run();
	}

	else if (argc == 2)
	{
		short int port = atoi(argv[1]);
		if( port < 1024 || port > 65535){
			std::cerr << "Ça va pas non ?"<<std::endl;
		}
		else
		{
			Serveur serveur(port);
			serveur.run();
		}
	}
	else
		std::cout<<"Erreur trop d'arguments"<<std::endl;

    return 0;
}
