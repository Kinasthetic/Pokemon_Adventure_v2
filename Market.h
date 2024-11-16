#pragma once

#include <iostream>
#include "globals.h"
using namespace std;

class Market
{
public:
    Market();
    void print();
    ~Market();
    void openLootBox();
    void buy(string item, int amnt);
};