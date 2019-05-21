#include "troll.h"
#include "enemy.h"
using namespace std;

Troll::Troll(int row, int col, Floor *f, char symbol, string type)
:Player{row, col, f, symbol, type} {
  hp = 120;
  starthp = 120;
  atk = 25;
  startatk = 25;
  def = 15;
  startdef = 15;
}

void Troll::attack(Enemy &e) {
  e.defense(*this);
  int r = e.getRow();
  int c = e.getCol();
  if (e.isDead()) {
  	pickupGold(e);
  	string sym{e.getSymbol(), 1};
  	f->actionAppend(sym + " is dead. ");
  	f->deleteEnOrPo(r,c);
  }
}
