#ifndef _HALFLING_H_
#define _HALFLING_H_
#include "enemy.h"
class Player;
class Troll;
class Vampire;

class Halfling : public Enemy {
public:
  Halfling(int row, int col, Floor *f, char symbol='L', std::string type="Halfling");
  void defense(Player &p) override;
  void defense(Vampire &p) override;
  void defense(Troll &p) override;
  void attack(Player &p) override;
};








#endif
