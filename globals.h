#pragma once

#include <vector>
#include <string>
#include <map>
#include "Player.h"
#include "Market.h"
using namespace std;

// Global variables
extern map<string, vector <string>> KantoPokemonList;
extern int KantoPokemonCount; // pokedex size
extern int PokeBoxCount; // pokebox size
extern Player player;
extern Market market;

void addKantoPokemon(string fileName); // reads Pokemon from file "KantoPokemon.txt" and adds them to the map

void printKantoPokemon(); // For testing and debugging purposes only
