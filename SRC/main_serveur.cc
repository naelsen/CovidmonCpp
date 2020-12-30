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
		short int p = atoi(argv[1]);
		if( p < 1024 || p > 65535){
			std::cerr << "Ça va pas non ?"<<std::endl;
		}
		else
		{
			Serveur serveur(p);
			serveur.run();
		}
	}
	else
		std::cout<<"Erreur trop d'arguments"<<std::endl;

    return 0;
}
