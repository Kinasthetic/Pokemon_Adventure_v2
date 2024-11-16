#include "globals.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

// Global variables
map<string, vector <string>> KantoPokemonList;
int KantoPokemonCount = 150;
int PokeBoxCount = 100;
Player player;
Market market;

// reads Pokemon from file "KantoPokemon.txt" and adds them to the map
void addKantoPokemon(string fileName)
{
    ifstream inFS(fileName);
    if (!inFS.is_open())
    {
        cout << "Could not open the file: " << fileName << ". The file may be corrupted or may not exist." << endl;
        // return;
    }

    string header;
    getline(inFS, header);

    string rarity, pokemon;
    while (getline(inFS, pokemon, ',') && getline(inFS, rarity)) {

        pokemon.erase(pokemon.find_last_not_of(" \n\r\t")+1);
        rarity.erase(rarity.find_last_not_of(" \n\r\t")+1);

        KantoPokemonList[rarity].push_back(pokemon);
    }

    inFS.close();
}

// For testing and debugging purposes only
void printKantoPokemon() {
    for (const auto& entry : KantoPokemonList) {
        cout << entry.first << ": ";
        for (const auto& pokemon : entry.second) {
            cout << pokemon << " ";
        }
        cout << endl << endl;
    }
}
