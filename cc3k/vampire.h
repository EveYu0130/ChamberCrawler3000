#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_
#include "player.h"
class Enemy;

class Vampire : public Player {
public:
  Vampire(int row, int col, Floor *f, char symbol='@', std::string type="Vampire");
  void attack(Enemy &e) override;
};



#endif
