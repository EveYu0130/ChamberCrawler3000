#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"
#include "treasure.h"
class Player;
class Vampire;
class Troll;

class Dragon : public Enemy {
  Treasure *dh;
public:
  Dragon(int row, int col, Floor *f, Treasure *dh, char symbol='D', std::string type="Dragon");
  void defense(Player &p) override;
  void defense(Vampire &p) override;
  void defense(Troll &p) override;
  void attack(Player &p) override;
  Treasure *getdh();
};







#endif
