#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Player.h"
#include "globals.h"
using namespace std;

class BasePokemon
{
public:
    BasePokemon(string name = "Unknown", string rarity = "Unknown") : name(name), rarity(rarity)
    {
        for (int i = 0; i < 6; ++i) {
            this->IVs.push_back(rand() % 32); // Generate IV between 0 and 31
        }
        int sum = 0;
        for (int iv : IVs) {
            sum += iv;
        }
        this->IV = ((static_cast<double>(sum) / 6) / 31) * 100; // Calculate average IV;
        this->level = rand() % 30 + 1; // Generate level between 1 and 30
        if (player.getShinyCharms() == 1)
        {
            this->isShiny = (rand() % 1365 == 0); // 1 in 1365 chance of being shiny
        }
        else
        {
            this->isShiny = (rand() % 4096 == 0); // 1 in 4096 chance of being shiny
        }
    }

    void printIVs()
    {
        cout << "IVs: ";
        for (int iv : IVs)
        {
            cout << iv << " ";
        }
    }
    string getName() { return name; }
    double getIV() { return IV; }
    int getLevel() { return level; }
    bool getIsShiny() { return isShiny; }
    string getRarity() { return rarity; }
    void setName(string name) { this->name = name; }
    void setIV(int IV) { this->IV = IV; }
    void setLevel(int level) { this->level = level; }
    void setIsShiny(bool isShiny) { this->isShiny = isShiny; }
    void setRarity(string rarity) { this->rarity = rarity; }
    virtual void print() = 0;
    virtual ~BasePokemon() {}

protected:
    string name;
    vector<int> IVs;
    double IV;
    int level;
    bool isShiny;
    string rarity;
};
