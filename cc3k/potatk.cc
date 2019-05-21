#include "potatk.h"
#include <string>
#include <cstdlib>
#include "player.h"
using namespace std;

PotATK::PotATK(int row, int col, bool obtainable, char symbol, string type)
 : Potion{row, col, obtainable, symbol, type} {
 	int i = rand() % 2;
 	if(i) isPositive = true;
 	else isPositive = false;
 	isUsed = false;
 	isPerm = false;
 }

bool PotATK::isKnown = false;

bool PotATK::getKnown() { return isKnown; }

void PotATK::setKnown() { isKnown = true; }

void PotATK::effect(Player *p) {
  if(isPositive) {
    p->update(0, 5, 0);
    p->getfloor()->actionAppend("PC uses BA. ");
  }
  else {
  	p->update(0, -5, 0);
    p->getfloor()->actionAppend("PC uses WA. ");
  }
  this->setUsed(true);
  this->setKnown();
}

void PotATK::magnified_effect(float times, Player *p) {
  int i = times * 5;
  if(isPositive) {
    p->update(0, i, 0);
    p->getfloor()->actionAppend("PC uses BA. ");
  }
  else {
  	p->update(0, -i, 0);
    p->getfloor()->actionAppend("PC uses WA. ");
  }
  this->setUsed(true);
  this->setKnown();
  cout << "end of mageffect" << endl;
}
