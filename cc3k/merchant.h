#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include "enemy.h"
class Player;
class Vampire;
class Troll;

class Merchant : public Enemy {
static bool Mhostile;
public:
  static void setMH();
  static bool getMH();
  Merchant(int row, int col, Floor *f, char symbol='M', std::string type="Merchant");
  void defense(Player &p) override;
  void defense(Vampire &p) override;
  void defense(Troll &p) override;
  void attack(Player &p) override;
};





#endif
