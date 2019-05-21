#include "goblin.h"
#include <cmath>
#include "enemy.h"
#include "dragon.h"
#include "orcs.h"
using namespace std;

Goblin::Goblin(int row, int col, Floor *f, char symbol, string type)
:Player{row, col, f, symbol, type} {
  hp = 110;
  starthp = 110;
  atk = 15;
  startatk = 15;
  def = 20;
  startdef = 20;
}


void Goblin::pickupGold(Enemy &e) {
  if (e.isDead()) {
    gold += 5;
    if ((e.getType()!="Dragon") && (e.getType()!="Merchant") && (e.getType()!="Human")) {
      gold += e.getgold();
    }
  }
}

void Goblin::defense(Orcs &o) {
  int i = rand() % 2;
  int damage = i? 0 : ceil((100/(100+def))*1.5*o.getatk());
  update(-damage, 0, 0);
  string s = to_string(damage);
  string sym{o.getSymbol(), 1};
  if (i) f->actionAppend(sym + " missed an attack. ");
  else f->actionAppend(sym + " deals " + s + " damage to PC. ");
}

void Goblin::attack(Enemy &e) {
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
