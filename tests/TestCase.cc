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
  Player P2(D);
  REQUIRE(S.get_port() == P.get_port());
  REQUIRE(P2.get_first_on_arene() == P.get_first_on_arene());
  P2.set_first_on_arene(true);
  P.set_first_on_arene(false);
  REQUIRE_FALSE(P.get_first_on_arene() == P2.get_first_on_arene());
}

TEST_CASE("2: Dresseur")
{
  Dresseur D1("Images/Personnages/M_zepekenia.png", "Zepekenia");
  REQUIRE(D1.get_current_bg() == choix_personnage);
  REQUIRE_FALSE(D1.get_choisi());
  Dresseur D2(D1);
  REQUIRE(D2.get_nom() == D1.get_nom());
  REQUIRE(D2.get_speed() == D1.get_speed());
  REQUIRE(D2.get_current_bg() == D1.get_current_bg());
}

TEST_CASE("3: Covidmon")
{
  Covidmon Draco("Images/Covidmons/F_dracofeu.png", "Dracofeu", Feu);
  Covidmon Torta("Images/Covidmons/E_tortank.png", "Tortank", Eau);
  Covidmon D2(Draco);
  Covidmon T2(Torta);
  REQUIRE(Draco.get_pv_max() == 650);
  REQUIRE(Torta.get_pv_max() == 800);
  REQUIRE(Draco.get_est_vivant());
  REQUIRE(D2.get_nom() == Draco.get_nom());
  REQUIRE(T2.get_current_bg()==Torta.get_current_bg());
}

TEST_CASE("4: Attaques")
{
  Attaque_de_loin A1("Images/Attaques/lance_vent.png", "Cru-aile");
  Attaque_de_pres A2("Images/Attaques/explosion_vent.png");
  Attaque_de_loin AC1(A1);
  Attaque_de_pres AC2(A2);
  REQUIRE(!A1.get_est_lancee());
  REQUIRE(A2.get_just_clicked());
  REQUIRE(AC1.get_degats()==A1.get_degats());
  REQUIRE(AC2.get_animation()==A2.get_animation());
  A1.set_just_clicked(true);
  AC1.set_just_clicked(false);
  REQUIRE_FALSE(A1.get_just_clicked() == AC1.get_just_clicked());
}
