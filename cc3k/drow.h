#ifndef _DROW_H_
#define _DROW_H_
#include "player.h"
class Enemy;

class Drow : public Player {
public:
  Drow(int row, int col, Floor *f, char symbol='@', std::string type="Drow");
  void defense(Elf &e) override;
  void attack(Enemy &e) override;
  void usePotion(std::string dir) override;
};




#endif
