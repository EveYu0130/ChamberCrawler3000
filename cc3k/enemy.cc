#include "enemy.h"
#include <cstdlib>
#include <cmath>
#include <string>
#include "treasure.h"
#include "player.h"
#include "vampire.h"
#include "troll.h"
#include "dragon.h"
using namespace std;

Enemy::Enemy(int row, int col, Floor *f, char symbol, std::string type)
:Character{row, col, f, symbol, type} {
  freezed = false;
}

int Enemy::getgold() { return golddrop; }

void Enemy::move() {
  if(!abletomove) return;
  int dir = rand() % 8; // 0->no; 1->so; 2->ea; 3->we
                        // 4->ne; 5->nw; 6->se; 7->sw
  int newrow;
  int newcol;
  while (1) {
    newrow = row;
    newcol = col;
    if (dir == 0) { --newrow; }
    else if (dir == 1) { ++newrow; }
    else if (dir == 2) { ++newcol; }
    else if (dir == 3) { --newcol; }
    else if (dir == 4) { --newrow; ++newcol; }
    else if (dir == 5) { --newrow; --newcol; }
    else if (dir == 6) { ++newrow; ++newcol; }
    else if (dir == 7) { ++newrow; --newcol; }
    string t = f->getCell(newrow, newcol)->getType();
    if (t=="FloorTile") {
      break;
    }
    dir = rand() % 8;
  }
  f->moveCell(this, newrow, newcol, false);
}

bool Enemy::isDead() { return hp<=0; }

Treasure *Enemy::dropTreasure() {
  return new Treasure{row, col, true, golddrop};
}

void Enemy::autoattack(int r, int c) {
  char s = f->getCell(r-1, c)->getSymbol();
  if (s == '@') {
    Player *p = dynamic_cast<Player*>(f->getCell(r-1, c));
    attack(*p);
    return;
  }
  s = f->getCell(r+1, c)->getSymbol();
  if (s == '@') {
    Player *p = dynamic_cast<Player*>(f->getCell(r+1, c));
    attack(*p);
    return;
  }
  s = f->getCell(r+1, c-1)->getSymbol();
  if (s == '@') {
    Player *p = dynamic_cast<Player*>(f->getCell(r+1, c-1));
    attack(*p);
    return;
  }
  s = f->getCell(r+1, c+1)->getSymbol();
  if (s == '@') {
    Player *p = dynamic_cast<Player*>(f->getCell(r+1, c+1));
    attack(*p);
    return;
  }
  s = f->getCell(r-1, c-1)->getSymbol();
  if (s == '@') {
    Player *p = dynamic_cast<Player*>(f->getCell(r-1, c-1));
    attack(*p);
    return;
  }
  s = f->getCell(r-1, c+1)->getSymbol();
  if (s == '@') {
    Player *p = dynamic_cast<Player*>(f->getCell(r-1, c+1));
    attack(*p);
    return;
  }
  s = f->getCell(r, c-1)->getSymbol();
  if (s == '@') {
    Player *p = dynamic_cast<Player*>(f->getCell(r, c-1));
    attack(*p);
    return;
  }
  s = f->getCell(r, c+1)->getSymbol();
  if (s == '@') {
    Player *p = dynamic_cast<Player*>(f->getCell(r, c+1));
    attack(*p);
    return;
  }
  move();
}

void Enemy::action() {
  if (freezed) return;
  int r = row;
  int c = col;
  autoattack(r, c);
  if (type == "Dragon") {
    Dragon *d = dynamic_cast<Dragon*>(this);
    r = d->getdh()->getRow();
    c = d->getdh()->getCol();
    autoattack(r, c);
  }
}


void Enemy::defense(Player &p) {
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Enemy::defense(Vampire &p) {
  p.update(5, 0, 0);
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Enemy::defense(Troll &p) {
  int damage = ceil((100/(float)(100+def))*p.getatk());
  update(-damage, 0, 0);
  string s{symbol, 1};
  string s2 = to_string(damage);
  string s3 = to_string(hp);
  f->actionAppend("PC deals " + s2 + " damage to " + s + " (" + s3 + " HP). ");
}

void Enemy::switchfreezed() {
  if (freezed) freezed = false;
  else freezed = true;
}
