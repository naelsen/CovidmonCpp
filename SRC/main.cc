#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "Game.hh"

// IP localhost : 127.0.0.1 (Pareil pour chaque ordi)

// Pour les autres IP si t'es sur Linux tape ca dans ton terminal pour avoir :
// IP local : hostname -I (Je crois que c'est celle la mais jsuis pas sur)
// IP publique : wget http://checkip.dyndns.org/ -O - -o /dev/null | cut -d: -f 2 | cut -d' ' -f 2 | cut -d\< -f 1

int main(int argc, char *argv[])
{
	Game game;
	game.run();
	return 0;
}