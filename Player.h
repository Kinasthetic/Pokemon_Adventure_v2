#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
using namespace std;

class Player
{
public:
    Player();
    void print();
    ~Player();
    void loadData(string fileName);
    string getName();
    char getGender();
    int getCoins();
    int getPokeballs();
    int getGreatballs();
    int getUltraballs();
    int getMasterballs();
    int getAmuletCoins();
    int getShinyCharms();
    int getLootboxesOpened();
    int getLifetimePokemonCaught();
    int getBallsUsed();
    void printPokebox(ostream& out);
    void printPokeboxWhenSaving(ostream& out);
    void printPokedex(ostream& out);
    void printPokedexWhenSaving(ostream& out);
    int getPokedexSize();
    int getPokeboxSize();
    void setName(string name);
    void setGender(char gender);
    void setCoins(int coins);
    void setPokeballs(int pokeballs);
    void setGreatballs(int greatballs);
    void setUltraballs(int ultraballs);
    void setMasterballs(int masterballs);
    void setAmuletCoins(int amuletCoins);
    void setShinyCharms(int shinyCharms);
    void setPokedexSize(int size);
    void setPokeboxSize(int size);
    void setLifetimePokemonCaught(int caught);
    void setLootboxesOpened(int boxes);
    void setBallsUsed(int balls);
    void addToDex(string pokemon);
    void addToBox(string pokemon, bool isShiny);
    void viewInv();
    int howMany(string pokemon);
    bool hasPokemon(string pokemon);
    string getPokemonRarity(string pokemon);
    void releasePokemon(string pokemon, int amnt);

private:
    string name;
    char gender;
    int coins;
    int pokeballs;
    int greatballs;
    int ultraballs;
    int masterballs;
    int amuletCoins;
    int shinyCharms;
    string* pokebox;
    string* pokedex;
    int pokeboxSize;
    int pokedexSize;
    int totalPokemonCaught;
    int lootboxesOpened;
    int ballsUsed;
};