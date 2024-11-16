#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>
#include "Player.h"
#include "globals.h"
using namespace std;

Player::Player()
{
  name = "Player";
  gender = '?';
  coins = 1000;
  pokeballs = 15;
  greatballs = 5;
  ultraballs = 1;
  masterballs = 0;
  amuletCoins = 0;
  shinyCharms = 0;
  pokebox = new string[PokeBoxCount];
  pokebox[0] = "None";
  pokedex = new string[KantoPokemonCount];
  pokedex[0] = "None";
  pokeboxSize = 0;
  pokedexSize = 0;
  totalPokemonCaught = 0;
  ballsUsed = 0;
  lootboxesOpened = 0;
}

void Player::print()
{
  cout << "Name: " << name << endl;
  cout << "Gender: " << gender << endl;
  cout << "Lifetime Pokémon Caught: " << totalPokemonCaught << endl;
  cout << "Life Balls Used: " << ballsUsed << endl;
}

Player::~Player()
{
  delete[] pokebox;
  delete[] pokedex;
}

void Player::loadData(string fileName)
{
  ifstream inFS(fileName);
    if (!inFS.is_open())
    {
      cout << "Error opening file: " << fileName << ". File data may be corrupted or may not exist." << endl;
      return;
    }

    string line;
    while (getline(inFS, line))
    {
        istringstream iss(line);
        string label;
        iss >> label; // Reads the label (e.g., "Player:")

        if (label == "Player:")
        {
          iss.ignore(1, ' ');
          getline(iss, name);
        }
        else if (label == "Gender:")
        {
          iss >> gender;
        }
        else if (label == "Pokécoins:")
        {
          iss >> coins;
        }
        else if (label == "Pokéballs:")
        {
          iss >> pokeballs;
        }
        else if (label == "Greatballs:")
        {
          iss >> greatballs;
        }
        else if (label == "Ultraballs:")
        {
          iss >> ultraballs;
        }
        else if (label == "Masterballs:")
        {
          iss >> masterballs;
        }
        else if (label == "Amulet")
        {
          string temp;
          iss >> temp; // Takes in "Coins:"
          iss >> amuletCoins; // Takes in the actual Amulet Coin
        }
        else if (label == "Shiny")
        {
          string temp;
          iss >> temp; // Takes in "Charms:"
          iss >> shinyCharms; // Takes in the actual Shiny Charm
        }
        else if (label == "Pokébox:")
        {
          if (line == "Your Pokébox is empty!")
            {
              pokeboxSize = 0; // If there's nothing in the pokebox, set the size to 0
            }
          else
          {
            // Reads pokebox entries until another label is found
            string* tempPokebox = new string[PokeBoxCount]; // Temp pokebox
            while (getline(inFS, line) && line.rfind("Pokébox entry", 0) == 0)
            {
              istringstream entryStream(line);
              string temp;
              entryStream >> temp; // Takes in "Pokebox"
              entryStream >> temp; // Takes in "entryX:"
              getline(entryStream, tempPokebox[pokeboxSize]);
              pokeboxSize++;
            }
            for (int i = 0; i < pokeboxSize; ++i)
            {
              pokebox[i] = tempPokebox[i];
            }
            delete[] tempPokebox;
          }
        }
        else if (label == "Pokédex:")
        {
          if (line == "Your Pokédex is empty!")
            {
              pokedexSize = 0; // If there's nothing in the pokedex, set the size to 0
            }
          else
          {
            // Reads pokedex entries until another label is found
            string* tempPokedex = new string[KantoPokemonCount];
            while (getline(inFS, line) && line.rfind("Pokédex entry", 0) == 0)
            {
              istringstream entryStream(line);
              string temp;
              entryStream >> temp; // Takes in "Pokedex"
              entryStream >> temp; // Takes in "entryX:"
              getline(entryStream, tempPokedex[pokedexSize]);
              pokedexSize++;
            }
            for (int i = 0; i < pokedexSize; ++i)
            {
              pokedex[i] = tempPokedex[i];
            }
            delete[] tempPokedex;
          }
        }
        else if (label == "Lifetime")
        {
          string temp;
          iss >> temp; // Takes in "Pokemon" or "Lootboxes"
          if (temp == "Pokémon")
          {
            iss >> temp; // Takes in "Caught:"
            iss >> totalPokemonCaught;
          }
          else if (temp == "Lootboxes")
          {
            iss >> temp; // Takes in "Opened:"
            iss >> lootboxesOpened;
          }
          else if (temp == "Balls")
          {
            iss >> temp; // Takes in "Used:"
            iss >> ballsUsed;
          }
        }
      }
  inFS.close();
}

string Player::getName() { return name; }
char Player::getGender() { return gender; }
int Player::getCoins() { return coins; }
int Player::getPokeballs() { return pokeballs; }
int Player::getGreatballs() { return greatballs; }
int Player::getUltraballs() { return ultraballs; }
int Player::getMasterballs() { return masterballs; }
int Player::getAmuletCoins() { return amuletCoins; }
int Player::getShinyCharms() { return shinyCharms; }
int Player::getLootboxesOpened() { return lootboxesOpened; }
int Player::getBallsUsed() { return ballsUsed; }

void Player::printPokebox(ostream& out)
{
  if (pokebox[0] != "None")
    {
    for (int i = 0; i < pokeboxSize; i++)
      {
        out << "Pokébox entry" << i + 1 << ": [" << char(getPokemonRarity(pokebox[i])[0]) << "] " << pokebox[i].erase(0, pokebox[i].find_first_not_of(" \t\n\r")) << endl;
      }
    }
    else
    {
      out << "Your Pokébox is empty!" << endl;
    }
}

void Player::printPokeboxWhenSaving(ostream& out)
{
  if (pokebox[0] != "None")
    {
    for (int i = 0; i < pokeboxSize; i++)
      {
        out << "Pokébox entry" << i + 1 << ": " << pokebox[i].erase(0, pokebox[i].find_first_not_of(" \t\n\r")) << endl;
      }
    }
    else
    {
      out << "Your Pokébox is empty!" << endl;
    }
}

void Player::printPokedex(ostream& out)
{
  if (pokedex[0] != "None")
    {
      for (int i = 0; i < pokedexSize; i++)
        {
          out << "Pokédex entry" << i + 1 << ": [" << char(getPokemonRarity(pokedex[i])[0]) << "] " << pokedex[i].erase(0, pokedex[i].find_first_not_of(" \t\n\r")) << endl;
        }
    }
    else
    {
      out << "Your Pokédex is empty!" << endl;
    }
}

void Player::printPokedexWhenSaving(ostream& out)
{
  if (pokebox[0] != "None")
    {
    for (int i = 0; i < pokedexSize; i++)
      {
        out << "Pokédex entry" << i + 1 << ": " << pokedex[i].erase(0, pokedex[i].find_first_not_of(" \t\n\r")) << endl;
      }
    }
    else
    {
      out << "Your Pokédex is empty!" << endl;
    }
}

int Player::getPokeboxSize() { return pokeboxSize; }
int Player::getPokedexSize() { return pokedexSize; }
int Player::getLifetimePokemonCaught() { return totalPokemonCaught; }

void Player::setName(string name) { this->name = name; }
void Player::setGender(char gender) { this->gender = gender; }
void Player::setCoins(int coins) { this->coins = coins; }
void Player::setPokeballs(int pokeballs) { this->pokeballs = pokeballs; }
void Player::setGreatballs(int greatballs) { this->greatballs = greatballs; }
void Player::setUltraballs(int ultraballs) { this->ultraballs = ultraballs; }
void Player::setMasterballs(int masterballs) { this->masterballs = masterballs; }
void Player::setAmuletCoins(int amuletCoins) { this->amuletCoins = amuletCoins; }
void Player::setShinyCharms(int shinyCharms) { this->shinyCharms = shinyCharms; }
void Player::setPokedexSize(int size) { this->pokedexSize = size; }
void Player::setPokeboxSize(int size) { this->pokeboxSize = size; }
void Player::setLifetimePokemonCaught(int caught) { this->totalPokemonCaught = caught; }
void Player::setLootboxesOpened(int boxes) { this->lootboxesOpened = boxes; }
void Player::setBallsUsed(int balls) { this->ballsUsed = balls; }

void Player::addToDex(string pokemon)
{
  pokemon.erase(0, pokemon.find_first_not_of(" \t\n\r"));
  bool isDuplicate = false;
  for (int i = 0; i < pokedexSize; i++)
  {
    if (pokedex[i] == pokemon)
    {
      isDuplicate = true;
      break;
    }
  }

  if (isDuplicate)
  {
    return;
  }

  pokedex[pokedexSize] = pokemon.erase(0, pokemon.find_first_not_of(" \t\n\r"));
  pokedexSize++;
  cout << pokemon << " has been added to your Pokédex!" << endl;
}

void Player::addToBox(string pokemon, bool isShiny)
{
  pokemon.erase(0, pokemon.find_first_not_of(" \t\n\r"));
  if (pokeboxSize < PokeBoxCount)
  {
    pokebox[pokeboxSize] = pokemon.erase(0, pokemon.find_first_not_of(" \t\n\r"));
    if (isShiny)
    {
      pokebox[pokeboxSize] += "✨";
    }
    pokeboxSize++;
    totalPokemonCaught++;
    cout << pokemon << " has been added to your Pokébox!" << endl;
  }
  else { cout << "Your Pokébox is full! Please release some Pokémon." << endl; }
}

void Player::viewInv()
{
  cout << "Coins: " << coins << endl;
  cout << "Pokéballs: " << pokeballs << endl;
  cout << "Greatballs: " << greatballs << endl;
  cout << "Ultraballs: " << ultraballs << endl;
  cout << "Masterballs: " << masterballs << endl;
  cout << "Amulet Coin: " << amuletCoins << endl;
  cout << "Shiny Charm: " << shinyCharms << endl;
}

int Player::howMany(string pokemon)
{
  int count = 0;
  for (int i = 0; i < pokeboxSize; i++)
    {
      if (pokebox[i] == pokemon)
      {
        count++;
      }
    }
  return count;
}

bool Player::hasPokemon(string pokemon)
{
  for (int i = 0; i < pokeboxSize; i++)
    {
      if (pokebox[i].erase(0, pokebox[i].find_first_not_of(" \t\n\r")) == pokemon)
      {
        return true;
      }
    }
  return false;
}

string Player::getPokemonRarity(string pokemon)
{
  for (auto& entry : KantoPokemonList)
    {
      if (find(entry.second.begin(), entry.second.end(), pokemon) != entry.second.end())
      {
        return entry.first;
      }
    }
  return "Unknown";
}

void Player::releasePokemon(string pokemon, int amnt)
{
  if (amnt > pokeboxSize)
  {
    cout << "You don't have that many Pokémon!" << endl;
  }
  else if (amnt < 1)
  {
    cout << "You can't release " << amnt << " Pokémon!" << endl;
  }
  else if (hasPokemon(pokemon) == false)
  {
    cout << "You don't have any " << pokemon << "!" << endl;
  }
  else if (amnt > howMany(pokemon))
  {
    cout << "You don't have that many " << pokemon << "!" << endl;
  }
  else
  {
    int countReleased = 0;
    for (int i = 0; i < pokeboxSize && countReleased < amnt; i++)
    {
        if (pokebox[i] == pokemon)
        {
          for (int j = i; j < pokeboxSize - 1; j++)
          {
              pokebox[j] = pokebox[j + 1];
          }
          pokeboxSize--;
          countReleased++;
          i--;
        }
    }
    cout << "You released " << amnt << " [" << char(getPokemonRarity(pokemon)[0]) << "] " << pokemon << "!" << endl;
    if (getPokemonRarity(pokemon) == "Common")
    {
      player.setCoins(player.getCoins() + amnt * 100);
      cout << "You earned " << amnt * 100 << " Pokécoins!" << endl;
    }
    else if (getPokemonRarity(pokemon) == "Uncommon")
    {
      player.setCoins(player.getCoins() + amnt * 250);
      cout << "You earned " << amnt * 250 << " Pokécoins!" << endl;
    }
    else if (getPokemonRarity(pokemon) == "Rare")
    {
      player.setCoins(player.getCoins() + amnt * 750);
      cout << "You earned " << amnt * 750 << " Pokécoins!" << endl;
    }
    else if (getPokemonRarity(pokemon) == "Super Rare")
    {
      player.setCoins(player.getCoins() + amnt * 1500);
      cout << "You earned " << amnt * 1500 << " Pokécoins!" << endl;
    }
    else if (getPokemonRarity(pokemon) == "Legendary")
    {
      player.setCoins(player.getCoins() + amnt * 5000);
      cout << "You earned " << amnt * 5000 << " Pokécoins!" << endl;
    }
    else if (getPokemonRarity(pokemon) == "Mythical")
    {
      player.setCoins(player.getCoins() + amnt * 10000);
      cout << "You earned " << amnt * 10000 << " Pokécoins!" << endl;
    }
    cout << "You now have " << player.getCoins() << " Pokécoins!" << endl;
  }
}
