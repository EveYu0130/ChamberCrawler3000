#include "dragon.h"
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <string>
#include "player.h"
#include "vampire.h"
#include "troll.h"
using namespace std;

Dragon::Dragon(int row, int col, Floor *f, Treasure *dh, char symbol, string type)
:Enemy{row, col, f, symbol, type}, dh{dh} {
  hp = 150;
  atk = 20;
  def = 20;
  golddrop = 6;
  hostile = true;
  abletomove = false;
}

void Dragon::defense(Player &p) {
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  string temp = "PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ";
  f->actionAppend(temp);
  cout << "DRAGON'S HP IS NOW " << gethp() << endl;
  cout << dh->getRow() << " " << dh->getCol() << endl;
  if (gethp() <= 0) {
  cout << "before obtainable" << endl;
    dh->setObtainable(true);
    
    cout << "after obtainable" << endl;
    f->actionAppend("The Dragon Hoard is ready to be picked up. ");
  }
}

void Dragon::defense(Vampire &p) {
  p.update(5, 0, 0);
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  string temp = "PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ";
  f->actionAppend(temp);
  cout << "DRAGON'S HP IS NOW " << gethp() << endl;
  if (gethp() <= 0) {
  cout << "before obtainable" << endl;
    dh->setObtainable(true);
    cout << "after obtainable" << endl;
    f->actionAppend("The Dragon Hoard is ready to be picked up. ");
  }
}

void Dragon::defense(Troll &p) {
  p.update(5, 0, 0);
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  string temp = "PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ";
  f->actionAppend(temp);
  cout << "DRAGON'S HP IS NOW " << gethp() << endl;
  if (gethp() <= 0) {
  cout << "before obtainable" << endl;
    dh->setObtainable(true);
    cout << "after obtainable" << endl;
    f->actionAppend("The Dragon Hoard is ready to be picked up. ");
  }
}

void Dragon::attack(Player &p) {
  if (hostile && !freezed) p.defense(*this);
}

Treasure *Dragon::getdh() { return dh; }
