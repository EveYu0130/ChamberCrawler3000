#include "drow.h"
#include <cmath>
#include <string>
#include "elf.h"
#include "potion.h"
#include "enemy.h"
using namespace std;

Drow::Drow(int row, int col, Floor *f, char symbol, string type)
: Player{row, col, f, symbol, type} {
  hp = 150;
  starthp = 150;
  atk = 25;
  startatk = 25;
  def = 15;
  startdef = 15;
}

void Drow::defense(Elf &e) {
  int i = rand() % 2;
  int damage = i? 0 : ceil((100/(100+def))*e.getatk());
  update(-damage, 0, 0);
  string s = to_string(damage);
  string sym{e.getSymbol(), 1};
  if (i) f->actionAppend(sym + " missed an attack. ");
  else f->actionAppend(sym + " deals " + s + " damage to PC. ");
}

void Drow::usePotion(string dir) {
  int newcol = col;
  int newrow = row;
  if (dir == "no") {
    --newrow;
  } else if (dir == "so") {
    ++newrow;
  } else if (dir == "ea") {
    ++newcol;
  } else if (dir == "we") {
    --newcol;
  } else if (dir == "ne") {
    ++newcol;
    --newrow;
  } else if (dir == "nw") {
    --newcol;
    --newrow;
  } else if (dir == "se") {
    ++newrow;
    ++newcol;
  } else if (dir == "sw") {
    ++newrow;
    --newcol;
  }
  char s = f->getCell(newrow, newcol)->getSymbol();
  if (s == 'P') {
    Potion *pot = dynamic_cast<Potion*>(f->getCell(newrow, newcol));
    pot->magnified_effect(1.5, this);
    f->deleteEnOrPo(newrow, newcol);
  }
}

void Drow::attack(Enemy &e) {
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
