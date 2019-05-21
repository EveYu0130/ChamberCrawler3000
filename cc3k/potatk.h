#ifndef _POTATK_H_
#define _POTATK_H_
#include <string>
#include "potion.h"

class Player;

class PotATK : public Potion {
  static bool isKnown;
 public:
  PotATK(int row, int col, bool obtainable, char symbol = 'P', std::string type = "PotATK");
  static bool getKnown();
  static void setKnown();
  void effect(Player *p) override;
  void magnified_effect(float times, Player *p) override;
};

#endif
