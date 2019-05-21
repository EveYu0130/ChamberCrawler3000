#ifndef _GOBLIN_H_
#define _GOBLIN_H_
#include "player.h"
class Enemy;

class Goblin : public Player {
public:
  Goblin(int row, int col, Floor *f, char symbol='@', std::string type="Goblin");
  void pickupGold(Enemy &e) override;
  void defense(Orcs &o) override;
  void attack(Enemy &e) override;
};

#endif
