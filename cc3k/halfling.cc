#include <cstdlib>
#include <cmath>
#include "halfling.h"
#include "player.h"
#include "vampire.h"
#include "troll.h"
using namespace std;

Halfling::Halfling(int row, int col, Floor *f, char symbol, string type)
:Enemy{row, col, f, symbol, type} {
  hp = 100;
  atk = 15;
  def = 20;
  int i = rand() % 2;
  if (i) golddrop = 1;
  else golddrop = 2;
  hostile = true;
  abletomove = true;
}

void Halfling::defense(Player &p) {
  int i = rand() % 2;
  int damage = i? 0 : ceil((100/(float)(100+def))*1.5*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  if (i) f->actionAppend("PC missed the attack to L. ");
  else f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Halfling::defense(Vampire &p) {
  int i = rand() % 2;
  if (!i) p.update(5, 0, 0);
  int damage = i? 0 : ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Halfling::defense(Troll &p) {
  p.update(5, 0, 0);
  int i = rand() % 2;
  int damage = i? 0 : ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Halfling::attack(Player &p) {
  if (hostile && !freezed) p.defense(*this);
}
