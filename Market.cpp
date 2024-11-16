#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "globals.h"
#include "Market.h"
using namespace std;

Market::Market() {}

void Market::print()
{
  cout << "You currently have " << player.getCoins() << " Pokécoins." << endl << endl;
  cout << "Here are the available items. Please choose an option:" << endl;
  cout << "1. Pokéballs : Cost - 200 PokéCoins." << endl;
  cout << "2. Greatballs : Cost - 500 PokéCoins." << endl;
  cout << "3. Ultraballs : Cost - 1500 PokéCoins." << endl;
  cout << "4. Masterballs : Cost - 10000 PokéCoins." << endl;
  if (player.getAmuletCoins() == 0)
  {
    cout << "5. Amulet Coin : Cost - 25000 PokéCoins. 1 in stock." << endl;
  }
  else
  {
    cout << "5. Amulet Coin : Cost - 25000 PokéCoins. 0 in stock. You have already bought this item!" << endl;
  }
  if (player.getShinyCharms() == 0)
  {
    cout << "6. Shiny Charm : Cost - 50000 PokéCoins. 1 in stock." << endl;
  }
  else{
    cout << "6. Shiny Charm : Cost - 50000 PokéCoins. 0 in stock. You have already bought this item!" << endl;
  }
  cout << "7. Lootbox : Cost - 2000 PokéCoins." << endl;
  cout << "8. Exit the Market." << endl;
}

Market::~Market() {}

void Market::openLootBox()
{
  int randomValue = rand() % 100;

  if (randomValue < 50) // 50% chance to get anywhere between 500 to 1000 coins
  {
    int randCoin = rand() % 501 + 500;
    player.setCoins(player.getCoins() + randCoin);
    cout << "You got " <<  randCoin << " PokéCoins! You now have " << player.getCoins() << " PokéCoins." << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  else if (randomValue < 50 + 30) // 30% chance to get anywhere between 10 to 30 Pokeballs
  {
    int randPokeBalls = rand() % 21 + 10;
    player.setPokeballs(player.getPokeballs() + randPokeBalls);
    cout << "You got " << randPokeBalls << " Pokéballs! You now have " << player.getPokeballs() << " Pokéballs." << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  else if (randomValue < 50 + 30 + 10) // 10% chance to get anywhere between 5 to 15 Greatballs
  {
    int randGreatBalls = rand() % 11 + 5;
    player.setGreatballs(player.getGreatballs() + randGreatBalls);
    cout << "You got " << randGreatBalls << " Greatballs! You now have " << player.getGreatballs() << " Greatballs." << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  else if (randomValue < 50 + 30 + 10 + 8) // 8% chance to get anywhere between 5 to 10 Ultraballs
  {
    int randUltraballs = rand() % 6 + 5;
    player.setUltraballs(player.getUltraballs() + randUltraballs);
    cout << "You got " << randUltraballs << " Ultraballs! You now have " << player.getUltraballs() << " Ultraballs." << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  else if (randomValue < 50 + 30 + 10 + 8 + 1.5) // 1.5% chance to get anywhere between 1 to 5 Masterballs
  {
    cout << "Whoa, nice!" << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));
    int randMasterballs = rand() % 5 + 1;
    player.setMasterballs(player.getMasterballs() + randMasterballs);
    cout << "You got " << randMasterballs << " Masterballs! You now have " << player.getMasterballs() << " Masterballs." << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  else if (randomValue < 50 + 30 + 10 + 8 + 1.5 + 0.49) // 0.49% chance to get an amulet coin
  {
    cout << "That's amazing..." << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));
    if (player.getAmuletCoins() == 0) // If the player doesn't have an amulet coin yet
    {
      player.setAmuletCoins(player.getAmuletCoins() + 1);
      cout << "You got an Amulet Coin! You now have " << player.getAmuletCoins() << " Amulet Coins. You cannot hold any more." << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
    else // If the player already has an amulet coin
    {
      player.setCoins(player.getCoins() + 25000);
      cout << "You already have an Amulet Coin!" << endl;
      cout << "You have traded the amulet coin for its shop value and gained some Pokécoins. You now have " << player.getCoins() << " PokéCoins." << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
  }
  else // 0.01% chance to get a shiny charm
  {
    cout << "I'm speechless..." << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));
    if (player.getShinyCharms() == 0) // If the player doesn't have a shiny charm yet
    {
      player.setShinyCharms(player.getShinyCharms() + 1);
      cout << "You got a Shiny Charm! You now have " << player.getShinyCharms() << " Shiny Charm. You cannot hold any more." << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
    else // If the player already has a shiny charm
    {
      player.setCoins(player.getCoins() + 50000);
      cout << "You already have a Shiny Charm!" << endl;
      cout << "You have traded the shiny charm for its shop value and gained some Pokécoins. You now have " << player.getCoins() << " PokéCoins." << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
  }
}

void Market::buy(string item, int amnt)
{
  if (item == "Pokeballs" || item == "Pokéballs") // Player wants to buy Pokeballs
  {
    if (player.getCoins() >= 200 * amnt) // If they can afford it
    {
      player.setCoins(player.getCoins() - 200 * amnt);
      player.setPokeballs(player.getPokeballs() + amnt);
      cout << "You bought " << amnt << " Pokéballs! You now have " << player.getPokeballs() << " Pokéballs." << endl;
      cout << "You now have " << player.getCoins() << " PokéCoins." << endl;
    }
    else // If they cant afford it
    {
      cout << "You don't have enough PokéCoins to buy " << amnt << " Pokéballs." << endl;
    }
  }

  else if (item == "Greatballs") // Player wants to buy Greatballs
  {
    if (player.getCoins() >= 500 * amnt) // If they can afford it
    {
      player.setCoins(player.getCoins() - 500 * amnt);
      player.setGreatballs(player.getGreatballs() + amnt);
      cout << "You bought " << amnt << " Greatballs! You now have " << player.getGreatballs() << " Greatballs." << endl;
      cout << "You now have " << player.getCoins() << " PokéCoins." << endl;
    }
    else // If they cant afford it
    {
      cout << "You don't have enough PokéCoins to buy " << amnt << " Greatballs." << endl;
    }
  }

  else if (item == "Ultraballs") // Player wants to buy Ultraballs
  {
    if (player.getCoins() >= 1500 * amnt) // If they can afford it
    {
      player.setCoins(player.getCoins() - 1500 * amnt);
      player.setUltraballs(player.getUltraballs() + amnt);
      cout << "You bought " << amnt << " Ultraballs! You now have " << player.getUltraballs() << " Ultraballs." << endl;
      cout << "You now have " << player.getCoins() << " PokéCoins." << endl;
    }
    else // If they cant afford it
    {
      cout << "You don't have enough PokéCoins to buy " << amnt << " Ultraballs." << endl;
    }
  }

  else if (item == "Masterballs") // Player wants to buy Masterballs
  {
    if (player.getCoins() >= 10000 * amnt) // If they can afford it
    {
      player.setCoins(player.getCoins() - 10000 * amnt);
      player.setMasterballs(player.getMasterballs() + amnt);
      cout << "You bought " << amnt << " Masterballs! You now have " << player.getMasterballs() << " Masterballs." << endl;
      cout << "You now have " << player.getCoins() << " PokéCoins." << endl;
    }
    else // If they cant afford it
    {
      cout << "You don't have enough PokéCoins to buy " << amnt << " Masterballs." << endl;
    }
  }

  else if (item == "Amulet Coin") // Player wants to buy an Amulet Coin
  {
    if (player.getCoins() >= 25000 * amnt) // If they can afford it
    {
      if (player.getAmuletCoins() == 0) // If they dont have an Amulet Coin
      {
        player.setCoins(player.getCoins() - 25000 * amnt);
        player.setAmuletCoins(player.getAmuletCoins() + amnt);
        cout << "You bought " << amnt << " Amulet Coin! You now have " << player.getAmuletCoins() << " Amulet Coins. You cannot hold any more." << endl;
        cout << "You now have " << player.getCoins() << " PokéCoins." << endl;
      }
      else // If they already have an Amulet Coin
      {
        cout << "You already have an Amulet Coin!" << endl;
      }
    }
    else // If they cant afford it
    {
      cout << "You don't have enough PokéCoins to buy " << amnt << " Amulet Coin." << endl;
    }
  }

  else if (item == "Shiny Charm") // Player wants to buy a Shiny Charm
  {
    if (player.getCoins() >= 50000 * amnt) // If they can afford it
    {
      if (player.getShinyCharms() == 0) // If they dont have a Shiny Charm
      {
        player.setCoins(player.getCoins() - 50000 * amnt);
        player.setShinyCharms(player.getShinyCharms() + amnt);
        cout << "You bought " << amnt << " Shiny Charm! You now have " << player.getShinyCharms() << " Shiny Charm. You cannot hold any more." << endl;
        cout << "You now have " << player.getCoins() << " PokéCoins." << endl;
      }
      else // If they already have a Shiny Charm
      {
        cout << "You already have a Shiny Charm!" << endl;
      }
    }
    else // If they cant afford it
    {
      cout << "You don't have enough PokéCoins to buy " << amnt << " Shiny Charm." << endl;
    }
  }

  else if (item == "Lootbox") // Player wants to buy a Lootbox"
  {
    if (player.getCoins() >= 2000 * amnt) // If they can afford it
    {
      player.setCoins(player.getCoins() - 2000 * amnt);
      for (int i = 0; i < amnt; i++)
        {
          openLootBox();
          player.setLootboxesOpened(player.getLootboxesOpened() + 1);
        }
    }
    else // If they cant afford it
    {
      cout << "You don't have enough PokéCoins to buy " << amnt << " Lootboxes." << endl;
    }
  }
}

