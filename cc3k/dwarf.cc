#include <cstdlib>
#include <cmath>
#include "dwarf.h"
#include "vampire.h"
#include "troll.h"
using namespace std;

Dwarf::Dwarf(int row, int col, Floor *f, char symbol, string type)
:Enemy{row, col, f, symbol, type} {
  hp = 100;
  atk = 20;
  def = 30;
  int i = rand() % 2;
  if (i) golddrop = 1;
  else golddrop = 2;
  hostile = true;
  abletomove = true;
}

void Dwarf::defense(Vampire &p) {
  p.update(-5, 0, 0);
  f->actionAppend("Vampire is allergic and loses 5 HP. ");
  int damage = ceil((100/(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  f->actionAppend("PC deals " + s2 + " damage to " + s + ". ");
}

void Dwarf::attack(Player &p) {
  if (hostile && !freezed) p.defense(*this);
}


void Dwarf::defense(Troll &p) {
  p.update(5, 0, 0);
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

