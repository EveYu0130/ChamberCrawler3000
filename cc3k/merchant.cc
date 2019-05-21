#include "merchant.h"
#include <cstdlib>
#include <cmath>
#include "player.h"
#include "vampire.h"
#include "troll.h"
using namespace std;


bool Merchant::Mhostile = false;

bool Merchant::getMH() { return Mhostile; }

void Merchant::setMH() { Mhostile = true; }

Merchant::Merchant(int row, int col, Floor *f, char symbol, string type)
:Enemy{row, col, f, symbol, type} {
  hp = 30;
  atk = 70;
  def = 5;
  golddrop = 4;
  hostile = false;
  abletomove = true;
}

void Merchant::defense(Player &p) {
  p.changeMattacked();
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  if (!Mhostile) {
  	f->actionAppend("All merchants become hostile. ");
  	setMH();
  }
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Merchant::defense(Vampire &p) {
  p.update(5, 0, 0);
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  if (!Mhostile) {
  	f->actionAppend("All merchants become hostile. ");
  	setMH();
  }
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Merchant::defense(Troll &p) {
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  if (!Mhostile) {
  	f->actionAppend("All merchants become hostile. ");
  	setMH();
  }
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Merchant::attack(Player &p) {
  if (Mhostile && !freezed) p.defense(*this);
}

