#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "character.h"
#include <string>

class Vampire;
class Troll;
class Player;
class Treasure;

class Enemy : public Character {
protected:
  int golddrop;
  bool hostile;
  bool abletomove;
  bool freezed;
public:
  Enemy(int row, int col, Floor *f, char symbol, std::string type);
  bool isDead();
  int getgold();
  void move();
  Treasure *dropTreasure();
  virtual void attack(Player &p)=0;
  virtual void action();
  void switchfreezed();
  virtual void autoattack(int r, int c);
  virtual void defense(Player &p);
  virtual void defense(Vampire &p);
  virtual void defense(Troll &p);
};


#endif
