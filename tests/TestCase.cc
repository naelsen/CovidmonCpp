// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <iostream>
#include <list>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

#include "../SRC/define.hh"
#include "../SRC/Dresseur.hh"
#include "../SRC/Image.hh"
#include "../SRC/Player.hh"
#include "../SRC/Covidmon.hh"
#include "../SRC/Attaque_de_loin.hh"
#include "../SRC/Attaque_de_pres.hh"
#include "../SRC/Serveur.hh"
#include "../SRC/Game.hh"


TEST_CASE("1: Serveur")
{
  Dresseur D("Images/Personnages/M_toto.png", "Toto");
  Serveur S;
  Player P(D);
  REQUIRE(S.get_port() == P.get_port());
}

TEST_CASE("2: Dresseur")
{
  Dresseur D1("Images/Personnages/M_zepekenia.png", "Zepekenia");
  REQUIRE(D1.get_current_bg() == choix_personnage);
  REQUIRE(!D1.get_choisi());
  Dresseur D2(D1);
  REQUIRE(D2.get_nom() == D1.get_nom());
}

TEST_CASE("3: Covidmon")
{
  Covidmon Draco("Images/Covidmons/F_dracofeu.png", "Dracofeu", Feu);
  Covidmon Torta("Images/Covidmons/E_tortank.png", "Tortank", Eau);
  REQUIRE(Draco.get_pv_max() == 650);
  REQUIRE(Torta.get_pv_max() == 800);
  REQUIRE(Draco.get_est_vivant());
}

TEST_CASE("4: Attaques")
{
  Attaque_de_loin A1("Images/Attaques/lance_vent.png", "Cru-aile");
  Attaque_de_pres A2("Images/Attaques/explosion_vent.png");
  REQUIRE(!A1.get_est_lancee());
  REQUIRE(A2.get_just_clicked());
  Attaque_de_loin AL(A1);
  REQUIRE(AL.get_degats()==A1.get_degats());
}
