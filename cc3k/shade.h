#ifndef _SHADE_H_
#define _SHADE_H_
#include "player.h"
class Enemy;

class Shade : public Player {
public:
  Shade(int row, int col, Floor *f, char symbol='@', std::string type="Shade");
  void attack(Enemy &e) override;
};







#endif
