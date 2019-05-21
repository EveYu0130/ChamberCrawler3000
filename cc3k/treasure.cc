#include "treasure.h"
#include "player.h"
using namespace std;

Treasure::Treasure(int row, int col, bool obtainable, int value, char symbol, string type)
 : Item{row, col, symbol, type, obtainable}, value{value} {
   picked = false;
 }

void Treasure::effect(Player *p) {
  p->addGold(value);
  picked = true;
}

bool Treasure::getPicked() { return picked; }

int Treasure::getValue() { return value; }
