#ifndef _TREASURE_H_
#define _TREASURE_H_
#include "item.h"

class Player;

class Treasure : public Item {
  int value;
  bool picked;
 public:
  Treasure(int row, int col, bool obtainable, int value, char symbol = 'G', std::string type = "Treasure");

  void effect(Player *p) override;
  bool getPicked();
  int getValue();
};

#endif
