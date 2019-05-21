#ifndef _POTDEF_H_
#define _POTDEF_H_
#include <string>
#include "potion.h"

class PotDEF : public Potion {
  static bool isKnown;
 public:
  PotDEF(int row, int col, bool obtainable, char symbol = 'P', std::string type = "PotDEF");
  static bool getKnown();
  static void setKnown();
  void magnified_effect(float times, Player *p) override;
  void effect(Player *p) override;
};

#endif
