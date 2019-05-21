#ifndef _ELF_H_
#define _ELF_H_
#include "enemy.h"
class Player;

class Troll;

class Elf : public Enemy {
public:
  Elf(int row, int col, Floor *f, char symbol='E', std::string type="Elf");
  void attack(Player &p) override;
  void defense(Troll &p) override;
};



#endif
