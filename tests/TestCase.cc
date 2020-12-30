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

TEST_CASE("1: Type de pokémon")
{
  Covidmon Draco("../Images/Covidmons/F_dracofeu.png", "Dracofeu", Feu);
  Covidmon Torta("../Images/Covidmons/E_tortank.png", "Tortank", Eau);
  REQUIRE(Draco.get_pv_max() == 650);
  std::cout << " ---------- Type Covidmon ---------------" << std::endl;
  REQUIRE(Draco.est_faible_contre(Torta));
  REQUIRE(Torta.est_fort_contre(Draco));
}














/*
TEST_CASE("2: Tableau2D with string")
{
  Tableau2D<std::string> tab(10,10,"");
  tab(1,3) = "ABC";
  REQUIRE(tab(1,3)== "ABC");
  REQUIRE(tab(3,3)== "");
  std::cout << " ----------- Tableau string --------------" << std::endl;
  std::cout << tab << std::endl;
}

TEST_CASE("3: Matrix operation avec un réel")
{
  Matrix<int> mat(5,5,0);
  mat(0,1) = 2;
  mat(1,0) = 3;

  mat =  5 * mat;
  REQUIRE(mat(0,1) == 10);
  REQUIRE(mat(1,0) == 15);

  mat =  mat * 2 ;
  REQUIRE(mat(0,1) == 20);
  REQUIRE(mat(1,0) == 30);

  mat =  mat / 2 ;
  REQUIRE(mat(0,1) == 10);
  REQUIRE(mat(1,0) == 15);
  
  std::cout << " -------- Matrix int -----------------" << std::endl;
  std::cout << mat << std::endl;
}

TEST_CASE("5: Matrix operation between matix")
{
  Matrix<float> a1(5, 5, 0);
  Matrix<float> a2(5, 5, 1);
  Matrix<float> a3 = a2;
  Matrix<float> a4 = 2 * (a1 + a2 + a3);
  for(size_t i = 0; i < 5; i++)
    for(size_t j = 0; j < 5; j++)
      CHECK(a4(i,j) == 4);

}

TEST_CASE("4: Matrix init")
{
  Matrix<float> a1(5, 5, Matrix<float>::identity);
  for(size_t i = 0; i < 5; i++)
    for(size_t j = 0; j < 5; j++)
      if(i==j)
        CHECK(a1(i,j) == 1);
      else
        CHECK(a1(i,j) == 0);

  std::cout << " ----------Matrix id ---------------" << std::endl;
  std::cout << a1 << std::endl;
  Matrix<float> a2(5, 5, 2);
  for(size_t i = 0; i < 5; i++)
    for(size_t j = 0; j < 5; j++)
        CHECK(a2(i,j) == 2);
  std::cout << " ---------matrix with init----------------" << std::endl;
  std::cout << a2 << std::endl;
}*/
