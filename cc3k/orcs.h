#ifndef _ORCS_H_
#define _ORCS_H_
#include "enemy.h"
class Player;

class Orcs : public Enemy {
public:
  Orcs(int row, int col, Floor *f, char symbol='O', std::string type="Orcs");
  void attack(Player &p) override;
};




#endif
