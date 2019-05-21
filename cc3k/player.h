#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "character.h"

class Enemy;
class Elf;
class Orcs;
class Potion;
class Treasure;

class Player : public Character {
protected:
  int gold;
  bool Mattacked;
  bool maxhp;
  int starthp;
  int startatk;
  int startdef;
  //bool PotUsed[6]; // [0]->RH; [1]->BA; [2]->BD; [3]->PH; [4]->WA; [5]->WD
public:
  Player(int row, int col, Floor *f, char symbol='@', std::string type="Player");
  void update(int hpchange, int atkchange, int defchange) override;
  bool isAlive();
  int getgold();
  void changeMattacked();
  void move(std::string direction);
  virtual void usePotion(std::string dir);
  void setnextfloor();
  void addGold(int value);
  void pickupTreasure(Treasure *t);
  void attackInDirection(std::string dir);
  virtual void attack(Enemy &e)=0;
  virtual void pickupGold(Enemy &e);
  virtual void defense(Enemy &e);
  virtual void defense(Elf &e);
  virtual void defense(Orcs &o);
  void setFloorAction(int r, int c);
};


#endif
