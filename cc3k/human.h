#ifndef _HUAMN_H_
#define _HUAMN_H_
#include "enemy.h"
class Player;

class Human : public Enemy {
public:
  Human(int row, int col, Floor *f, char symbol='H', std::string type="Human");
  void attack(Player &p) override;
};



#endif
