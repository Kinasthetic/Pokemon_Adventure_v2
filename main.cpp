#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>
#include <limits>
#include <cctype>
#include <cstdio>
#include "globals.h"
#include "KantoPokemon.h"
#include "Player.h"
using namespace std;

bool fileExists(string& filename)
{
  ifstream inFS(filename);
  return inFS.good();
}

int starterChoice()
{
  int choice = 0;
  cout << "Which Pokémon would you like to choose?" << endl << endl;
  this_thread::sleep_for(chrono::seconds(1));
  cout << "1. Bulbasaur" << endl;
  cout << "2. Charmander" << endl;
  cout << "3. Squirtle" << endl;
  while (choice != 1 && choice != 2 && choice != 3)
    {
      cin >> choice;
      if ((choice == 1) || (choice == 2) || (choice == 3))
        {
          return choice;
        }
      else
      {
        continue;
      }
    }
  return choice;
}

void saveGame()
{
  ofstream outFS("savedGame.txt");
  outFS << "Player: " << player.getName() << endl;
  outFS << "Gender: " << player.getGender() << endl;
  outFS << "Pokecoins: " << player.getCoins() << endl;
  outFS << "Pokéballs: " << player.getPokeballs() << endl;
  outFS << "Greatballs: " << player.getGreatballs() << endl;
  outFS << "Ultraballs: " << player.getUltraballs() << endl;
  outFS << "Masterballs: " << player.getMasterballs() << endl;
  outFS << "Amulet Coins: " << player.getAmuletCoins() << endl;
  outFS << "Shiny Charms: " << player.getShinyCharms() << endl;
  outFS << "Pokébox: " << endl;
  player.printPokeboxWhenSaving(outFS);
  outFS << "Pokébox Size: " << player.getPokeboxSize() << endl;
  outFS << "Pokédex: " << endl;
  player.printPokedexWhenSaving(outFS);
  outFS << "Pokédex Size: " << player.getPokedexSize() << endl;
  outFS << "Lifetime Pokémon Caught: " << player.getLifetimePokemonCaught() << endl;
  outFS << "Lifetime Lootboxes Opened: " << player.getLootboxesOpened() << endl;
  outFS << "Lifetime Balls Used: " << player.getBallsUsed() << endl;
}

int coinsFromCatch(string pokemon)
{
  string rarity = player.getPokemonRarity(pokemon);
    if (rarity == "Common")
    {
      if (player.getAmuletCoins() == 1)
      {
        return rand() % 151 + 150;
      }
      else
      {
        return rand() % 201 + 100;
      }
    }
    else if (rarity == "Uncommon")
    {
      if (player.getAmuletCoins() == 1)
      {
        return rand() % 126 + 375;
      }
      else
      {
        return rand() % 251 + 250;
      }
    }
    else if (rarity == "Rare")
    {
      if (player.getAmuletCoins() == 1)
      {
        return rand() % 201 + 600;
      }
      else
      {
        return rand() % 401 + 400;
      }
    }
    else if (rarity == "Super Rare")
    {
      if (player.getAmuletCoins() == 1)
      {
        return rand() % 751 + 2250;
      }
      else
      {
        return rand() % 501 + 1500;
      }
    }
    else if (rarity == "Legendary")
    {
      if (player.getAmuletCoins() == 1)
      {
        return rand() % 2501 + 12500;
      }
      else
      {
        return rand() % 5001 + 10000;
      }
    }
    else if (rarity == "Mythical")
    {
      if (player.getAmuletCoins() == 1)
      {
        return rand() % 2501 + 22500;
      }
      else
      {
        return rand() % 5001 + 20000;
      }
    }
  else
  {
    return 0;
  }
}

void ellipses(int seconds)
{
  for (int i = 0; i < seconds; i++)
  {
    cout << ".";
    cout.flush();
    this_thread::sleep_for(chrono::seconds(1));
  }
  cout << endl;
}

int main()
{
  srand(time(0));
  cout << fixed << setprecision(2);
  addKantoPokemon("KantoPokemon.txt");
  string input;
  int fixedOption;
  int marketOption = 0;
  int marketAmnt = 0;
  int exploreOption = 0;
  bool isDoneForReal = false;

  cout << "Welcome to Pokémon Adventure: Kanto Edition, a Pokémon game right in the terminal!" << endl;
  this_thread::sleep_for(chrono::seconds(1));
  cout << "Thank you for playing! :)" << endl;
  this_thread::sleep_for(chrono::seconds(2));
  cout << "Detecting if you have a save file";
  ellipses(3);
  string fileName = "savedGame.txt";
  bool loadFile = false;
  bool isDone = false;
  while (fileExists(fileName) && loadFile == false && isDone == false)
  {
    cout << "We found a save file!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl;
    char saveInput = '?';
    cout << "Welcome back, " << player.getName() << "! Do you want to load your save file? (y/n)" << endl;
    while (saveInput != 'y' && saveInput != 'n')
      {
        cin >> saveInput;
        if (saveInput == 'y' || saveInput == 'n')
        {
          break;
        }
      }
    if (saveInput == 'y')
    {
      cout << "Loading saved game";
      ellipses(3);
      cout << endl;
      player.loadData(fileName);
      cout << "Hello, " << player.getName() << "! Your game has been loaded." << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
      isDone = true;
      isDoneForReal = true;
    }
    else if (saveInput == 'n')
    {
      cout << "Deleting your data";
      ellipses(3);
      if (remove(fileName.c_str()) == 0)
      {
        cout << "Your data has been deleted." << endl << endl;
      }
      else
      {
        cout << "Error deleting your data. The file may be corrupted or may not exist." << endl << endl;
      }
      this_thread::sleep_for(chrono::seconds(1));
      loadFile = true;
      isDone = true;
      break;
    }
  }
  loadFile = true;
  if (loadFile == true && isDoneForReal == false)
  {
    cout << "No save file found. Starting new game";
    ellipses(3);
    cout << endl;
    cout << "Please type c when you want to continue." << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Hey trainer! I'm Professor Oak! I'm here to help you on your journey!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    while (input != "c")
      {
        cin >> input;
        if (input == "c")
        {
          break;
        }
      }
    input = "";
    cout << "You can call me Oak! I'm a Pokémon Professor!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    while (input != "c")
      {
        cin >> input;
        if (input == "c")
        {
          break;
        }
      }
    input = "";
    cout << "Pokémon are such lovely creatures, and I can't wait for you to venture out and explore and catch some of your own!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    while (input != "c")
      {
        cin >> input;
        if (input == "c")
        {
          break;
        }
      }
    input = "";
    cout << "But before you venture off in the wild, you need to pick your first Pokémon!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    while (input != "c")
      {
        cin >> input;
        if (input == "c")
        {
          break;
        }
      }
    input = "";
    cout << "We have these 3 lovely Pokémons waiting for you!" << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Meet Bulbasaur, the Grass Pokémon!" << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Meet Charmander, the Fire Pokémon!" << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "And finally, meet Squirtle, the Water Pokémon!" << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
    int sChoice = starterChoice();
    if (sChoice == 1)
    {
      cout << "Wow! Bulbsaur is a great choice!" << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
      player.addToDex("Bulbasaur");
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
      player.addToBox("Bulbasaur", false);
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
    else if (sChoice == 2)
    {
      cout << "Wow! Charmander is a great choice!" << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
      player.addToDex("Charmander");
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
      player.addToBox("Charmander", false);
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
    else if (sChoice == 3)
    {
      cout << "Wow! Squirtle is a great choice!" << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
      player.addToDex("Squirtle");
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
      player.addToBox("Squirtle", false);
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Now that you have your first Pokémon, you can start your journey! Good luck on your adventure!" << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));
    string name;
    char gender = '?';
    cout << "What's your name?" << endl;
    cin >> name;
    while (name == "Admin" || name == "admin")
      {
        if (name != "Admin" && name != "admin")
        {
          break;
        }
        cout << "You cannot have that name! Only the actual admin can :)" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "What's your name?" << endl;
        cin >> name;
      }
      cout << "What's your gender? Please type either 'm' or 'f'." << endl;
    while (gender != 'm' && gender != 'f')
      {
        cin >> gender;
        if (gender == 'm' || gender == 'f')
        {
          break;
        }
        else
        {
          cout << "Please type either 'm' or 'f'." << endl;
        }
      }
    player.setName(name);
    player.setGender(gender);
    cout << "Hello " << player.getName() << "! Your adventure awaits!" << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Saving your data, please wait";
    ellipses(3);
    saveGame();
    cout << "Game saved. You are now being teleported to the Kanto Region!" << endl << endl;
  }

  cout << "Starting game, please wait";
  ellipses(3);
  cout << endl;

  cout << "Welcome! Please select an option to either 1. Explore or 2. View the other options." << endl;
  int option = 0;
  while (option != 1 && option != 2)
    {
      cin >> option;
      if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 1 or 2." << endl;
            continue;
        }
      if (option == 1) // If the player chooses to explore
      {
        exploreOption = 1;
        cout << "You have chosen to explore the Kanto Region!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Please wait";
        ellipses(3);
        break;
      }
      else if (option == 2) // If the player chooses something else
      {
        cout << "You have chosen to view the other options!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Please choose between: " << endl;
        cout << "1. Open the market." << endl;
        cout << "2. View your Pokémon." << endl;
        cout << "3. View your Pokédex." << endl;
        cout << "4. Release Pokémon." << endl;
        cout << "5. View your inventory." << endl;
        cout << "6. View your stats." << endl;
        cout << "7. Save your game." << endl;
        cout << "8. Save and quit the game." << endl;
        cout << "9. Quit the game without saving." << endl;
        cout << "10. Go explore!" << endl;
        cout << "11. Go item hunting!" << endl;
        cin >> fixedOption;
        break;
      }
      else
      {
        cout << "You have chosen an option other than 1 or 2. The game will default you to the 2nd option. Please wait." << endl << endl;
        option = 2;
        this_thread::sleep_for(chrono::seconds(2));
        break;
      }
    }

  bool isRunning = true;
  int coins = 0;
  char rarityInitial = '?';
  int ballRollRate = 0;
  bool isMarketAlreadySeen = false;
  while (isRunning)
  {
    while (exploreOption == 1) // Until the player quits exploring
    {
      if ((player.getPokeballs() == 0) && (player.getGreatballs() == 0) && (player.getUltraballs() == 0) && (player.getMasterballs() == 0))
      {
        cout << "You have no balls! Please go to the market or go on an item hunt to find some!" << endl;
        fixedOption = 0;
        exploreOption = 0;
        break;
      }
      char move;
      cout << "Enter your move (w/a/s/d to move, q to quit): ";
      cin >> move;

      if (move != 'q' && move != 'w' && move != 'a' && move != 's' && move != 'd')
      {
        cout << "Invalid move. Please try again." << endl;
        continue;
      }
      if (move == 'q') // If the player chooses to quit, break out of this loop
      {
        fixedOption = 0;
        exploreOption = 0;
        break;
      }
      else
      {
        cout << endl;
      }
        // Generates a new Pokemon encouter
        KantoPokemon newPokemon;
        string rarity = newPokemon.chooseRarity();
        string name = newPokemon.choosePokemon(rarity);
        newPokemon.setName(name);
        newPokemon.setRarity(rarity);
        rarityInitial = char(newPokemon.getRarity()[0]);

        if (newPokemon.getRarity() == "Legendary")
        {
          cout << "What's this";
          ellipses(3);
          cout << endl;
          cout << "HUH?!" << endl << endl;
          this_thread::sleep_for(chrono::seconds(2));
          cout << player.getName() << ", a LEGENDARY Pokemon has appeared!" << endl << endl;
          this_thread::sleep_for(chrono::seconds(1));
        }
        else if (newPokemon.getRarity() == "Mythical")
        {
          cout << "The sun sure is bright";
          ellipses(3);
          cout << endl;
          cout << "Wait, that's no sun, that's";
          ellipses(3);
          cout << endl;
          cout << player.getName() << ", a MYTHICAL Pokemon has appeared!" << endl << endl;
          this_thread::sleep_for(chrono::seconds(1));
        }
        if (newPokemon.getIsShiny())
        {
          ellipses(3);
          cout << "These colors seem unusual... ✨" << endl << endl;
          this_thread::sleep_for(chrono::seconds(2));
        }

        cout << "You encountered ";
        if (newPokemon.getName()[0] == 'A' || newPokemon.getName()[0] == 'E' ||     newPokemon.getName()[0] == 'I' || newPokemon.getName()[0] == 'O' || newPokemon.getName()[0] == 'U')
        {
          cout << "an " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl;
        }
        else
        {
          cout << "a " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl;
        }
        cout << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "What ball do you want to use? Use the abbreviations of the ball to catch the Pokémon." << endl;
        cout << "pb: Pokéball | Amount remaining: " <<  player.getPokeballs() << endl;
        cout << "gb: Greatball | Amount remaining: " <<  player.getGreatballs() << endl;
        cout << "ub: Ultraball | Amount remaining: " <<  player.getUltraballs() << endl;
        cout << "mb: Masterball | Amount remaining: " <<  player.getMasterballs() << endl;
        cout << "e: Escape" << endl;
        string ball;
          while (ball != "pb" && ball != "gb" && ball != "ub" && ball != "mb" && ball != "e")
          {
            cin >> ball;
            if (ball == "pb" || ball == "gb" || ball == "ub" || ball == "mb" || ball == "e")
            {
              break;
            }
          }
        if (ball == "e")
        {
          cout << "You have escaped the encounter." << endl << endl;
          this_thread::sleep_for(chrono::seconds(1));
          continue;
        }
        else if (ball == "pb")
        {
          if (player.getPokeballs() < 1)
          {
            cout << "You don't have any Pokéballs! Escaping the encounter." << endl << endl;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
          }
          player.setBallsUsed(player.getBallsUsed() + 1);
          ballRollRate = rand() % 100 + 1;
          if (ballRollRate <= 50) // 50% chance of the Pokeball catching
          {
            cout << endl;
            coins = coinsFromCatch(newPokemon.getName());
            cout << "You caught ";
            if (newPokemon.getName()[0] == 'A' || newPokemon.getName()[0] == 'E' ||     newPokemon.getName()[0] == 'I' || newPokemon.getName()[0] == 'O' || newPokemon.getName()[0] == 'U')
            {
              cout << "an " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl << endl;
            }
            else
            {
              cout << "a " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl << endl;
            }
            this_thread::sleep_for(chrono::seconds(1));
            player.addToDex(newPokemon.getName());
            player.addToBox(newPokemon.getName(), newPokemon.getIsShiny());
            cout << endl;
            player.setPokeballs(player.getPokeballs() - 1);
            cout << "You have " << player.getPokeballs() << " Pokéballs left." << endl << endl;
            player.setCoins(player.getCoins() + coins);
            cout << "You gained " << coins << " Pokécoins from this catch!" << endl;
            if (player.getAmuletCoins() == 1)
            {
              cout << "You gained an extra 50% Pokécoins from your Amulet Coin!" << endl;
            }
            cout << "You now have " << player.getCoins() << " Pokécoins." << endl << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Info about this Pokémon: " << endl << endl;
            newPokemon.print();
            cout << endl;
          }
          else
          {
            cout << "The Pokéball broke." << endl;
            player.setPokeballs(player.getPokeballs() - 1);
            cout << "You have " << player.getPokeballs() << " Pokéballs left." << endl << endl;
          }
          this_thread::sleep_for(chrono::seconds(1));
          cout << endl;
          continue;
        }
        else if (ball == "gb")
        {
          if (player.getGreatballs() < 1)
          {
            cout << "You don't have any Greatballs! Escaping the encounter." << endl << endl;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
          }
          player.setBallsUsed(player.getBallsUsed() + 1);
          ballRollRate = rand() % 100 + 1;
          if (ballRollRate <= 65) // 65% chance of the Greatball catching
          {
            cout << endl;
            coins = coinsFromCatch(newPokemon.getName());
            cout << "You caught ";
            if (newPokemon.getName()[0] == 'A' || newPokemon.getName()[0] == 'E' ||     newPokemon.getName()[0] == 'I' || newPokemon.getName()[0] == 'O' || newPokemon.getName()[0] == 'U')
            {
              cout << "an " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl << endl;
            }
            else
            {
              cout << "a " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl << endl;
            }
            this_thread::sleep_for(chrono::seconds(1));
            player.addToDex(newPokemon.getName());
            player.addToBox(newPokemon.getName(), newPokemon.getIsShiny());
            player.setGreatballs(player.getGreatballs() - 1);
            cout << endl;
            cout << "You have " << player.getGreatballs() << " Greatballs left." << endl << endl;
            player.setCoins(player.getCoins() + coins);
            cout << "You gained " << coins << " Pokécoins from this catch!" << endl;
            if (player.getAmuletCoins() == 1)
            {
              cout << "You gained an extra 50% Pokécoins from your Amulet Coin!" << endl;
            }
            cout << "You now have " << player.getCoins() << " Pokécoins." << endl << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Info about this Pokémon: " << endl << endl;
            newPokemon.print();
            cout << endl;
          }
          else
          {
            cout << "The Greatball broke." << endl;
            player.setGreatballs(player.getGreatballs() - 1);
            cout << "You have " << player.getGreatballs() << " Greatballs left." << endl << endl;
          }
          this_thread::sleep_for(chrono::seconds(1));
          cout << endl;
          continue;
        }
        else if (ball == "ub")
        {
          if (player.getUltraballs() < 1)
          {
            cout << "You don't have any Ultraballs! Escaping the encounter." << endl << endl;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
          }
          player.setBallsUsed(player.getBallsUsed() + 1);
          ballRollRate = rand() % 100 + 1;
          if (ballRollRate <= 75) // 75% chance of the Ultraball catching
          {
            cout << endl;
            coins = coinsFromCatch(newPokemon.getName());
            cout << "You caught ";
            if (newPokemon.getName()[0] == 'A' || newPokemon.getName()[0] == 'E' ||     newPokemon.getName()[0] == 'I' || newPokemon.getName()[0] == 'O' || newPokemon.getName()[0] == 'U')
            {
              cout << "an " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl << endl;
            }
            else
            {
              cout << "a " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl << endl;
            }
            this_thread::sleep_for(chrono::seconds(1));
            player.addToDex(newPokemon.getName());
            player.addToBox(newPokemon.getName(), newPokemon.getIsShiny());
            player.setUltraballs(player.getUltraballs() - 1);
            cout << endl;
            cout << "You have " << player.getUltraballs() << " Ultraballs left." << endl << endl;
            player.setCoins(player.getCoins() + coins);
            cout << "You gained " << coins << " Pokécoins from this catch!" << endl;
            if (player.getAmuletCoins() == 1)
            {
              cout << "You gained an extra 50% Pokécoins from your Amulet Coin!" << endl;
            }
            cout << "You now have " << player.getCoins() << " Pokécoins." << endl << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Info about this Pokémon: " << endl << endl;
            newPokemon.print();
            cout << endl;
          }
          else
          {
            cout << "The Ultraball broke." << endl;
            player.setUltraballs(player.getUltraballs() - 1);
            cout << "You have " << player.getUltraballs() << " Ultraballs left." << endl << endl;
          }
          this_thread::sleep_for(chrono::seconds(1));
          cout << endl;
          continue;
        }
        else if (ball == "mb") // 100% chance of the Masterball catching
        {
          if (player.getMasterballs() < 1)
          {
            cout << "You don't have any Masterballs! Escaping the encounter." << endl << endl;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
          }
          player.setBallsUsed(player.getBallsUsed() + 1);
          cout << endl;
          coins = coinsFromCatch(newPokemon.getName());
          cout << "You caught ";
          if (newPokemon.getName()[0] == 'A' || newPokemon.getName()[0] == 'E' ||     newPokemon.getName()[0] == 'I' || newPokemon.getName()[0] == 'O' || newPokemon.getName()[0] == 'U')
          {
            cout << "an " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl << endl;
          }
          else
          {
            cout << "a " << "[" << rarityInitial << "] " << newPokemon.getName() << "!" << endl << endl;
          }
          this_thread::sleep_for(chrono::seconds(1));
          player.addToDex(newPokemon.getName());
          player.addToBox(newPokemon.getName(), newPokemon.getIsShiny());
          player.setMasterballs(player.getMasterballs() - 1);
          cout << endl;
          cout << "You have " << player.getMasterballs() << " Masterballs left." << endl << endl;
          player.setCoins(player.getCoins() + coins);
          cout << "You gained " << coins << " Pokécoins from this catch!" << endl;
          if (player.getAmuletCoins() == 1)
          {
            cout << "You gained an extra 50% Pokécoins from your Amulet Coin!" << endl;
          }
          cout << "You now have " << player.getCoins() << " Pokécoins." << endl << endl;
          this_thread::sleep_for(chrono::seconds(1));
          cout << "Info about this Pokémon: " << endl << endl;
          newPokemon.print();
          cout << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
        cout << endl;
        continue;
      }
    while (exploreOption == 2)
      {
        char input2 = '?';
        cout << "Type e to explore, or q to quit." << endl;
        while (input2 != 'e' && input2 != 'q')
          {
            cin >> input2;
            if (input2 == 'e' || input2 == 'q')
            {
              break;
            }
          }
        if (input2 == 'q')
        {
          cout << "You have quit item hunting." << endl << endl;
          this_thread::sleep_for(chrono::seconds(1));
          exploreOption = 0;
          fixedOption = 0;
          break;
        }
        cout << "Exploring the area..." << endl << endl;
        this_thread::sleep_for(chrono::seconds(1));
        int outcome = rand() % 10000 + 1;
        if (outcome <= 5000) // 50% chance of finding anywhere between 100 - 200 Pokecoins
          {
            int newCoins = 0;
            if (player.getAmuletCoins() == 1)
            {
              newCoins = 150 + rand() % 151;
            }
            else
            {
              newCoins = 100 + rand() % 101;
            }
            player.setCoins(player.getCoins() + newCoins);
            cout << "You found " << newCoins << " Pokécoins!" << endl;
            if (player.getAmuletCoins() == 1)
            {
              cout << "You gained an extra 50% Pokécoins from your Amulet Coin!" << endl;
            }
            cout << "You now have " << player.getCoins() << " Pokécoins." << endl << endl;
            this_thread::sleep_for(chrono::seconds(1));
          }
          else if (outcome <= 8000) // 30% chance of finding anywhere between 5 - 15 Pokeballs
          {
            int newPokeballs = 5 + rand() % 11;
            player.setPokeballs(player.getPokeballs() + newPokeballs);
            cout << "You found " << newPokeballs << " Pokéballs!" << endl;
            cout << "You now have " << player.getPokeballs() << " Pokéballs." << endl << endl;
          }
          else if (outcome <= 9000) // 10% chance of finding anywhere between 5 - 15 Greatballs
          {
            int newGreatballs = 5 + rand() % 11;
            player.setGreatballs(player.getGreatballs() + newGreatballs);
            cout << "You found " << newGreatballs << " Greatballs!" << endl;
            cout << "You now have " << player.getGreatballs() << " Greatballs." << endl << endl;
          }
          else if (outcome <= 9700) // 7% chance of finding anywhere between 5 - 10 Ultraballs
          {
            int newUltraballs = 5 + rand() % 6;
            player.setUltraballs(player.getUltraballs() + newUltraballs);
            cout << "You found " << newUltraballs << " Ultraballs!" << endl;
            cout << "You now have " << player.getUltraballs() << " Ultraballs." << endl << endl;
          }
          else if (outcome <= 9900) // 2% chance of finding anywhere between 2 - 5 Masterballs
          {
            int newMasterballs = 2 + rand() % 4;
            player.setMasterballs(player.getMasterballs() + newMasterballs);
            cout << "Nice, good job!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "You found " << newMasterballs << " Masterballs!" << endl;
            cout << "You now have " << player.getMasterballs() << " Masterballs." << endl << endl;
          }
          else if (outcome <= 9950) // 0.5% chance of finding an Amulet Coin
          {
            if (player.getAmuletCoins() == 1)
            {
              cout << "You already have an Amulet Coin!" << endl;
              cout << "Converting it to Pokécoins..." << endl << endl;
              this_thread::sleep_for(chrono::seconds(1));
              player.setCoins(player.getCoins() + 25000);
              cout << "You now have " << player.getCoins() << " Pokécoins." << endl << endl;
            }
            else
            {
              player.setAmuletCoins(player.getAmuletCoins() + 1);
              cout << "I can't believe it..." << endl;
              this_thread::sleep_for(chrono::seconds(2));
              cout << "You found an Amulet Coin!" << endl;
              cout << "You now have " << player.getAmuletCoins() << " Amulet Coin." << endl << endl;
            }
          }
          else if (outcome <= 9960) // 0.1% chance of finding a Shiny Charm
          {
            if (player.getShinyCharms() == 1)
            {
              cout << "You already have a Shiny Charm!" << endl;
              cout << "Converting it to Pokécoins..." << endl << endl;
              this_thread::sleep_for(chrono::seconds(1));
              player.setCoins(player.getCoins() + 50000);
              cout << "You now have " << player.getCoins() << " Pokécoins." << endl << endl;
            }
            else
            {
              player.setShinyCharms(player.getShinyCharms() + 1);
              cout << "You're a madman..." << endl;
              this_thread::sleep_for(chrono::seconds(2));
              cout << "You found a Shiny Charm!" << endl;
              cout << "You now have " << player.getShinyCharms() << " Shiny Charm." << endl << endl;
            }
          }
          else if (outcome <= 9999) // 0.39% chance of finding anywhere between 10 - 30 lootboxes
          {
            int newLootboxes = 10 + rand() % 21;
            cout << "You found " << newLootboxes << " Lootboxes! Opening them now." << endl << endl;
            for (int i = 0; i < newLootboxes; i++)
              {
                market.openLootBox();
                this_thread::sleep_for(chrono::seconds(1));
              }
          }
          else // 0.01% chance of hitting a jackpot
          {
            int jackpot = 30000 + rand() % 5001;
            player.setCoins(player.getCoins() + jackpot);
            cout << "Is that what I think it is? The end of the rainbow...?" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "You found a jackpot worth " << jackpot << " Pokécoins!" << endl;
            cout << "You now have " << player.getCoins() << " Pokécoins." << endl << endl;
          }

      }
    while (fixedOption < 1 || fixedOption > 11) // If they chose to quit exploring
      {
        cout << "What would you like to do?" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Please choose between: " << endl;
        cout << "1. Open the market." << endl;
        cout << "2. View your Pokémon." << endl;
        cout << "3. View your Pokédex." << endl;
        cout << "4. Release Pokémon." << endl;
        cout << "5. View your inventory." << endl;
        cout << "6. View your stats." << endl;
        cout << "7. Save your game." << endl;
        cout << "8. Save and quit the game." << endl;
        cout << "9. Quit the game without saving." << endl;
        cout << "10. Go explore!" << endl;
        cout << "11. Go item hunting!" << endl;
        cin >> fixedOption;
      }
    while (fixedOption == 1) // View the market
      {
        if (isMarketAlreadySeen == false)
        {
          cout << endl;
          cout << "Welcome to the Pokémon Market!" << endl << endl;
          this_thread::sleep_for(chrono::seconds(1));
        }
        isMarketAlreadySeen = true;
        market.print();
        cin >> marketOption;
        if (marketOption == 1) // Pokeballs
        {
          cout << "How many Pokéballs would you like to buy?" << endl;
          while (marketAmnt < 1)
            {
              cin >> marketAmnt;
            }
          market.buy("Pokeballs", marketAmnt);
          cout << endl;
          this_thread::sleep_for(chrono::seconds(1));
          marketAmnt = 0;
        }
        else if (marketOption == 2) // Greatballs
        {
          cout << "How many Greatballs would you like to buy?" << endl;
          while (marketAmnt < 1)
          {
            cin >> marketAmnt;
          }
          market.buy("Greatballs", marketAmnt);
          cout << endl;
          this_thread::sleep_for(chrono::seconds(1));
          marketAmnt = 0;
        }
        else if (marketOption == 3) // Ultraballs
        {
          cout << "How many Ultraballs would you like to buy?" << endl;
          while (marketAmnt < 1)
          {
            cin >> marketAmnt;
          }
          market.buy("Ultraballs", marketAmnt);
          cout << endl;
          this_thread::sleep_for(chrono::seconds(1));
          marketAmnt = 0;
        }
        else if (marketOption == 4) // Masterballs
        {
          cout << "How many Masterballs would you like to buy?" << endl;
          while (marketAmnt < 1)
          {
            cin >> marketAmnt;
          }
          market.buy("Masterballs", marketAmnt);
          cout << endl;
          this_thread::sleep_for(chrono::seconds(1));
          marketAmnt = 0;
        }
        else if (marketOption == 5) // Amulet Coin
        {
          cout << "Buying an Amulet Coin";
          ellipses(2);
          market.buy("Amulet Coin", 1);
          cout << endl;
          this_thread::sleep_for(chrono::seconds(1));
          marketAmnt = 0;
        }
        else if (marketOption == 6) // Shiny Charm
        {
          cout << "Buying a Shiny Charm";
          ellipses(2);
          market.buy("Shiny Charm", 1);
          cout << endl;
          this_thread::sleep_for(chrono::seconds(1));
          marketAmnt = 0;
        }
        else if (marketOption == 7) // Lootbox
        {
          cout << "How many Lootboxes would you like to buy?" << endl;
          while (marketAmnt < 1)
          {
            cin >> marketAmnt;
          }
          market.buy("Lootbox", marketAmnt);
          cout << endl;
          this_thread::sleep_for(chrono::seconds(1));
          marketAmnt = 0;
        }
        else if (marketOption == 8)
        {
          cout << "You have chosen to exit. Exiting the market";
          ellipses(3);
          cout << endl;
          marketAmnt = 0;
          fixedOption = 0;
          isMarketAlreadySeen = false;
          break;
        }
        else
        {
          cout << "Please choose a valid option 1-8." << endl << endl;
          continue;
        }
      }
    if (fixedOption == 2) // View Pokebox
      {
        cout << "You have chosen to view your Pokémon!" << endl << endl;
        player.printPokebox(cout);
        cout << endl;
        this_thread::sleep_for(chrono::seconds(1));
        fixedOption = 0;
      }
    else if (fixedOption == 3) // View Pokdex
    {
      cout << "You have chosen to view your Pokédex!" << endl << endl;
      player.printPokedex(cout);
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
      fixedOption = 0;
    }
    else if (fixedOption == 4) // Release Pokemon
    {
      cout << "You have chosen to release Pokémon!" << endl;
      if (player.getPokeboxSize() == 0)
      {
        cout << "You have no Pokémon to release!" << endl << endl;
        fixedOption = 0;
      }
      else
      {
        cout << "Which Pokémon would you like to release?" << endl << endl;
        cout << "Your Pokébox: " << endl;
        player.printPokebox(cout);
        cout << endl;
        cout << "Please type the name of the Pokémon you would like to release. Please remember this is case-sensitive. Type 'q' if you want to quit." << endl;
        string releaseName;
        cin >> releaseName;
        if (releaseName == "q")
        {
          cout << "You have chosen to exit. Exiting the release menu";
          ellipses(3);
          cout << endl;
          fixedOption = 0;
          continue;
        }
        cout << "How many " << releaseName << " would you like to release?" << endl;
        int releaseAmnt = 0;
        while (releaseAmnt < 1)
          {
            cin >> releaseAmnt;
          }
        cout << "Attempting to release " << releaseAmnt << " " << releaseName;
        ellipses(3);
        player.releasePokemon(releaseName, releaseAmnt);
        cout << endl;
        this_thread::sleep_for(chrono::seconds(1));
        fixedOption = 0;
      }
    }
    else if (fixedOption == 5) // View Inventory
    {
      cout << "You have chosen to view your inventory!" << endl;
      player.viewInv();
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
      fixedOption = 0;
    }
    else if (fixedOption == 6) // View Stats
    {
      cout << "You have chosen to view your stats!" << endl;
      player.print();
      cout << endl;
      this_thread::sleep_for(chrono::seconds(1));
      fixedOption = 0;
    }
    else if (fixedOption == 7) // Save Game
    {
      cout << "You have chosen to save your game!" << endl;
      cout << "Saving game, please wait";
      ellipses(3);
      saveGame();
      cout << endl;
      cout << "Your game has been saved!" << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
      fixedOption = 0;
    }
    else if (fixedOption == 8) // Save and Quit
    {
      cout << "You have chosen to save and quit the game!" << endl;
      cout << "Saving game, please wait";
      ellipses(3);
      saveGame();
      cout << endl;
      cout << "Your game has been saved!" << endl << endl;
      this_thread::sleep_for(chrono::seconds(1));
      cout << "Thank you for playing! See you again soon!" << endl;
      exit(5);
    }
    else if (fixedOption == 9) // Quit without saving
    {
      cout << "You have chosen to quit the game without saving!" << endl;
      cout << "Are you sure you want to quit? (y/n)" << endl;
      char quitOption = '?';
      while (quitOption != 'y' && quitOption != 'n')
        {
          cin >> quitOption;
          if (quitOption == 'y' || quitOption == 'n')
          {
            break;
          }
        }
      if (quitOption == 'y')
      {
        cout << "Thank you for playing! See you again soon!" << endl;
        fixedOption = 0;
        break;
      }
      else if (quitOption == 'n')
      {
        cout << "You have chosen to continue playing!" << endl << endl;
        this_thread::sleep_for(chrono::seconds(1));
        fixedOption = 0;
      }
    }
    else if (fixedOption == 10) // Explore
    {
      cout << "You have chosen to explore!" << endl;
      this_thread::sleep_for(chrono::seconds(1));
      cout << "Please wait";
      ellipses(3);
      exploreOption = 1;
      fixedOption = 0;
      continue;
    }
    else if (fixedOption == 11) // Item Hunting
    {
      cout << "You have chosen to go item hunting!" << endl;
      cout << "Please wait";
      ellipses(3);
      exploreOption = 2;
      fixedOption = 0;
      continue;
    }
    else if (fixedOption > 11 || fixedOption < 0) // Invalid Option
    {
      cout << "Please choose a valid option 1-10." << endl << endl;
      continue;
      fixedOption = 0;
    }
  }

  return 0;
}