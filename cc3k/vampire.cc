#include "vampire.h"
#include "enemy.h"
#include <cstdlib>
using namespace std;

Vampire::Vampire(int row, int col, Floor *f, char symbol, string type)
:Player{row, col, f, symbol, type} {
  hp = 50;
  starthp = 50;
  atk = 25;
  startatk = 25;
  def = 25;
  startdef = 25;
}

void Vampire::attack(Enemy &e) {
  e.defense(*this);
  cout << e.gethp() << endl;
  int r = e.getRow();
  int c = e.getCol();
  if (e.isDead()) {
  	pickupGold(e);
  	string sym{e.getSymbol(), 1};
  	f->actionAppend(sym + " is dead. ");
  	f->deleteEnOrPo(r,c);
  }
}

