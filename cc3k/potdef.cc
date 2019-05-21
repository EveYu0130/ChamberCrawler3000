#include "potdef.h"
#include <string>
#include <cstdlib>
#include "player.h"
using namespace std;

PotDEF::PotDEF(int row, int col, bool obtainable, char symbol, string type)
 : Potion{row, col, obtainable, symbol, type} {
 	int i = rand() % 2;
 	if(i) isPositive = true;
 	else isPositive = false;
 	isUsed = false;
 	isPerm = false;
 }

bool PotDEF::isKnown = false;

bool PotDEF::getKnown() { return isKnown; }

void PotDEF::setKnown() { isKnown = true; }

void PotDEF::effect(Player *p) {
  if(isPositive) {
    p->update(0, 0, 5);
    p->getfloor()->actionAppend("PC uses BD. ");
  }
  else {
  	p->update(0, 0, -5);
    p->getfloor()->actionAppend("PC uses WD. ");
  }
  this->setUsed(true);
  this->setKnown();
}

void PotDEF::magnified_effect(float times, Player *p) {
  int i = times * 5;
  if(isPositive) {
    p->update(0, 0, i);
    p->getfloor()->actionAppend("PC uses BD. ");
  }
  else {
  	p->update(0, 0, -i);
    p->getfloor()->actionAppend("PC uses WD. ");
  }
  this->setUsed(true);
  this->setKnown();
  cout << "end of mageffect" << endl;
}
