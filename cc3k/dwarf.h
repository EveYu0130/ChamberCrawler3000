#ifndef _DWARF_H_
#define _DWARF_H_
#include "enemy.h"
class Player;
class Vampire;
class Troll;


class Dwarf : public Enemy {
public:
  Dwarf(int row, int col, Floor *f, char symbol='W', std::string type="Dwarf");
  void defense(Vampire &p) override;
  void attack(Player &p) override;
  void defense (Troll &p) override;
};



#endif
