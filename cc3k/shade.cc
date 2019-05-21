#include "shade.h"
#include "enemy.h"
using namespace std;

Shade::Shade(int row, int col, Floor *f, char symbol, std::string type)
: Player{row, col, f, symbol, type} {
  hp = 125;
  starthp = 125;
  atk = 25;
  startatk = 25;
  def = 25;
  startdef = 25;
}

void Shade::attack(Enemy &e) {
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

