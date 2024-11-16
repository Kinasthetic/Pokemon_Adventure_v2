#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include "KantoPokemon.h"
#include "globals.h"
using namespace std;

KantoPokemon::KantoPokemon() : BasePokemon() {}

KantoPokemon::KantoPokemon(string name, string rarity) : BasePokemon(name, rarity)
{}

void KantoPokemon::print()
{
    cout << "Name: " << name << endl;
    cout << "IV: " << IV << "%" << endl;
    printIVs();
    cout << endl;
    cout << "Level: " << level << endl;
    cout << "Shiny: " << (isShiny ? "Yes" : "No") << endl;
    cout << "Rarity: " << rarity << endl;
}

KantoPokemon::~KantoPokemon() {}

int KantoPokemon::rollRate()
{
    int randomValue = rand() % 10000;

    if (randomValue < 5000) { return 0; } // 50% chance (Common)
    else if (randomValue < 5000 + 3500) { return 1; } // 35% chance (Uncommon)
    else if (randomValue < 5000 + 3500 + 1200) { return 2; } // 12% chance (Rare)
    else if (randomValue < 5000 + 3500 + 1200 + 200) {return 3; } // 2% chance (Super rare)
    else if (randomValue < 5000 + 3500 + 1200 + 200 + 99) { return 4; } // 0.99% chance (Legendary)
    else { return 5; } // 0.01% chance (Mythical)
}

string KantoPokemon::chooseRarity() {
    int rarityIndex = rollRate();
    switch (rarityIndex) {
        case 0: return "Common";
        case 1: return "Uncommon";
        case 2: return "Rare";
        case 3: return "Super Rare";
        case 4: return "Legendary";
        case 5: return "Mythical";
        default: return "Unknown";
    }
}

string KantoPokemon::choosePokemon(string rarity)
{
    vector<string>& pokemonList = KantoPokemonList[rarity];
    int randomIndex = rand() % pokemonList.size();
    return pokemonList[randomIndex];
}

