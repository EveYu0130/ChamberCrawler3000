#include "elf.h"
#include <cstdlib>
#include <cmath>
#include "player.h"
#include "troll.h"
using namespace std;

Elf::Elf(int row, int col, Floor *f, char symbol, string type)
:Enemy{row, col, f, symbol, type} {
  hp = 140;
  atk = 30;
  def = 10;
  int i = rand() % 2;
  if (i) golddrop = 1;
  else golddrop = 2;
  hostile = true;
  abletomove = true;
}


void Elf::attack(Player &p) {
  if (hostile && !freezed) p.defense(*this);
}



void Elf::defense(Troll &p) {
  p.update(5, 0, 0);
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}
