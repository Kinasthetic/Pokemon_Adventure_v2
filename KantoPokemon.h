#include "BasePokemon.h"
#include "globals.h"
#include <iostream>
using namespace std;

class KantoPokemon : public BasePokemon
{
public:
    KantoPokemon();
    KantoPokemon(string name, string rarity);
    void print();
    ~KantoPokemon();
    int rollRate();
    string chooseRarity();
    string choosePokemon(string rarity);

};
