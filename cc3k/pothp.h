#ifndef _POTHP_H_
#define _POTHP_H_
#include <string>
#include "potion.h"

class PotHP : public Potion {
  static bool isKnown;
 public:
  PotHP(int row, int col, bool obtainable, char symbol = 'P', std::string type = "PotHP");
  static bool getKnown();
  static void setKnown();
  void effect(Player *p) override;
  void magnified_effect(float times, Player *p) override;
};

#endif
