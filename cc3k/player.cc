#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "orcs.h"
#include "elf.h"
#include "treasure.h"
#include "pothp.h"
#include "potatk.h"
#include "potdef.h"
using namespace std;

Player::Player(int row, int col, Floor *f, char symbol, string type)
: Character{row, col, f, symbol, type} {
  gold = 0;
  Mattacked = false;
  hp = 125;
  starthp = 125;
  atk = 25;
  startatk = 25;
  def = 25;
  startdef = 25;
  if (type == "Vampire") maxhp = false;
  else maxhp = true;
}

void Player::update(int hpchange, int atkchange, int defchange) {
  if (hp+hpchange > starthp) {
    if (maxhp) hp = starthp;
    else hp += hpchange;
  } else {
    hp = hp+hpchange<0? 0 : hp+hpchange;
  }
  atk = atk+atkchange<0? 0 : atk+atkchange;
  def = def+defchange<0? 0 : def+defchange;
}

bool Player::isAlive() {
	return hp > 0;
}

void Player::move(string dir) {
  int newcol = col;
  int newrow = row;
  string s;
  if (dir == "no") {
    --newrow;
    s = "North";
  } else if (dir == "so") {
    ++newrow;
    s = "South";
  } else if (dir == "ea") {
    ++newcol;
    s = "East";
  } else if (dir == "we") {
    --newcol;
    s = "West";
  } else if (dir == "ne") {
    ++newcol;
    --newrow;
    s = "NorthEast";
  } else if (dir == "nw") {
    --newcol;
    --newrow;
    s = "NorthWest";
  } else if (dir == "se") {
    ++newrow;
    ++newcol;
    s = "SouthEast";
  } else if (dir == "sw") {
    ++newrow;
    --newcol;
    s = "SouthWest";
  }
  string t = f->getCell(newrow, newcol)->getType();
  if (t=="FloorTile" || t=="Doorway" || t=="Passage" || t=="Stair" || t=="Treasure") {
    f->actionAppend("PC moves "+ s + ". ");
    if (t=="Treasure") {
    	Treasure *t = dynamic_cast<Treasure *>(f->getCell(newrow, newcol));
    	pickupTreasure(t);
    	int val = t->getValue();
    	cout << t->getObtainable() << endl;
    	if(t->getObtainable()) {
    	    string v = to_string(val);
      		this->setPrev('.');
      		f->actionAppend("PC picks up " + v + " gold. ");
      		f->moveCell(this, newrow, newcol, false);
    	} else f->moveCell(this, newrow, newcol, true);
  	}
  	else if (t=="Stair") {
  		f->moveCell(this, newrow, newcol, false);
    	f->moveUp();
    	f->actionAppend("PC moves to the next floor. ");
  	}
    else f->moveCell(this, newrow, newcol, false);
  }
  else {
    f->actionAppend("Walk somewhere else! ");
  }

  int r = row;
  int c = col;
  char s1 = f->getCell(r-1, c)->getSymbol();
  if (s1 == 'P') {
  	setFloorAction(r-1, c);
    return;
  }
  s1 = f->getCell(r+1, c)->getSymbol();
  if (s1 == 'P') {
    setFloorAction(r+1, c);
    return;
  }
  s1 = f->getCell(r+1, c-1)->getSymbol();
  if (s1 == 'P') {
    setFloorAction(r+1, c-1);
    return;
  }
  s1 = f->getCell(r+1, c+1)->getSymbol();
  if (s1 == 'P') {
    setFloorAction(r+1, c+1);
    return;
  }
  s1 = f->getCell(r-1, c-1)->getSymbol();
  if (s1 == 'P') {
    setFloorAction(r-1, c-1);
    return;
  }
  s1 = f->getCell(r-1, c+1)->getSymbol();
  if (s1 == 'P') {
    setFloorAction(r-1, c+1);
    return;
  }
  s1 = f->getCell(r, c-1)->getSymbol();
  if (s1 == 'P') {
    setFloorAction(r, c-1);
  }
  s1 = f->getCell(r, c+1)->getSymbol();
  if (s1 == 'P') {
    setFloorAction(r, c+1);
    return;
  }
}

void Player::setFloorAction(int r, int c) {
	PotHP *p = dynamic_cast<PotHP*>(f->getCell(r, c));
	if (p) {
		if (p->getKnown()) f->actionAppend("PC sees an HP potion. ");
		else f->actionAppend("PC sees an unknown Potion. ");
	}
	else {
		PotDEF *p = dynamic_cast<PotDEF*>(f->getCell(r, c));
		if (p) {
			if (p->getKnown()) f->actionAppend("PC sees an DEF potion. ");
			else f->actionAppend("PC sees an unknown Potion. ");
		}
		else {
		PotATK *p = dynamic_cast<PotATK*>(f->getCell(r, c));
		if (p->getKnown()) f->actionAppend("PC sees an ATK potion. ");
		else f->actionAppend("PC sees an unknown Potion. ");
		}
	}
}


int Player::getgold() { return gold; }

void Player::changeMattacked() { Mattacked = true; }

void Player::usePotion(string dir) {
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
  cout << s;
  if (s == 'P') {
    Potion *pot = dynamic_cast<Potion*>(f->getCell(newrow, newcol));
    pot->effect(this);
    f->deleteEnOrPo(newrow, newcol);
  }
}

void Player::attackInDirection(std::string dir) {
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
  if (s=='H'||s=='W'||s=='E'||s=='O'||s=='M'||s=='D'||s=='L') {
    Enemy *e = dynamic_cast<Enemy*>(f->getCell(newrow, newcol));
    attack(*e);
  }
}

void Player::setnextfloor() {
  atk = startatk;
  def = startdef;
}

void Player::addGold(int value) {
  gold += value;
}

void Player::pickupTreasure(Treasure *t) {
  if(t->getObtainable()) {
   t->effect(this);
   this->setPrev('.');
   }
}

void Player::pickupGold(Enemy &e) {
  if (e.isDead() && (e.getType()!="Dragon") && (e.getType()!="Merchant") && (e.getType()!="Human")) {
    gold += e.getgold();
  }
}


void Player::defense(Enemy &e) {
  int i = rand() % 2;
  int damage = i? 0 : ceil((100/(float)(100+def))*e.getatk());
  cout << damage << endl;
  cout << "Inside default defnse" << endl;
  update(-damage, 0, 0);
  string s = to_string(damage);
  string s1{e.getSymbol(), 1};
  if (i) f->actionAppend(s1+" missed an attack. ");
  else f->actionAppend(s1 + " deals " + s + " damage to PC. ");
}


void Player::defense(Elf &e) {
  int i = rand() % 2;
  int damage = i? 0 : ceil((100/(float)(100+def))*e.getatk());
  cout << damage << endl;
  update(-damage, 0, 0);
  string s1 = to_string(damage);
  string sym{e.getSymbol(), 1};
  if (i) {
  	f->actionAppend( sym + " missed the first attack. ");
  }
  else f->actionAppend(sym + " deals " + s1 + " damage in the first attack to PC. ");
  i = rand() % 2;
  damage = i? 0 : ceil((100/(float)(100+def))*e.getatk());
  cout << damage << endl;
  update(-damage, 0, 0);
  if (i) f->actionAppend(sym + " missed the second attack. ");
  else f->actionAppend(sym + " deals " + s1 + " damage in the second attack to PC. ");
}

void Player::defense(Orcs &o) {
  int i = rand() % 2;
  int damage = i? 0 : ceil((100/(float)(100+def))*o.getatk());
  cout << damage << endl;
  update(-damage, 0, 0);
  string s2 = to_string(damage);
  string sym{o.getSymbol(), 1};
  if (i) f->actionAppend(sym + " missed an attack. ");
  else f->actionAppend(sym + " deals " + s2 + " damage to PC. ");
}
