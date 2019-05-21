#include "pothp.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include "player.h"
using namespace std;

PotHP::PotHP(int row, int col, bool obtainable, char symbol, string type)
 : Potion{row, col, obtainable, symbol, type} {
 	int i = rand() % 2;
 	if(i) isPositive = true;
 	else isPositive = false;
 	isUsed = false;
 	isPerm = true;
 }

bool PotHP::isKnown = false;

bool PotHP::getKnown() { return isKnown; }

void PotHP::setKnown() { isKnown = true; }

void PotHP::effect(Player *p) {
  if(isPositive) {
    p->update(10, 0, 0);
    p->getfloor()->actionAppend("PC uses RH. ");
  }
  else {
  	p->update(-10, 0, 0);
    p->getfloor()->actionAppend("PC uses PH. ");
  }
  this->setUsed(true);
  this->setKnown();
}

void PotHP::magnified_effect(float times, Player *p) {
  int i = times * 10;
  if(isPositive) {
    p->update(i, 0, 0);
    p->getfloor()->actionAppend("PC uses RH. ");
  }
  else {
  	p->update(-i, 0, 0);
    p->getfloor()->actionAppend("PC uses PH. ");
  }
  this->setUsed(true);
  this->setKnown();
  cout << "end of mageffect" << endl;
}
