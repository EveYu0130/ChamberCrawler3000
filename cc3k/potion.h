#ifndef _POTION_H_
#define _POTION_H_
#include <string>
#include "item.h"

class Player;

class Potion : public Item {
protected:
  bool isPositive;
  bool isUsed;
  bool isPerm;
  std::string potName;
public:
  Potion(int row, int col, bool obtainable, char symbol='P', std::string type="Potion");

  bool getPositive() const;
  bool getUsed() const;
  bool getPerm() const;
  std::string getPotName() const;

  void setPositive(bool isPos);
  void setUsed(bool isUsed);
  void setPerm(bool isPerm);
  virtual void magnified_effect(float times, Player *p)=0;
};

#endif
