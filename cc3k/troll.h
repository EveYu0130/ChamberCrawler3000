#ifndef _TROLL_H_
#define _TROLL_H_
#include "player.h"
class Enemy;

class Troll : public Player {
public:
  Troll(int row, int col, Floor *f, char symbol='@', std::string type="Troll");
  void attack(Enemy &e) override;
};




#endif
