#ifndef _ITEM_H_
#define _ITEM_H_
#include "cell.h"

class Player;

class Item : public Cell {
  bool obtainable;
 public:
  Item(int row, int col, char symbol, std::string type, bool obtainable);
  void setObtainable(bool obtainable);
  bool getObtainable() const;
  virtual void effect(Player *p) = 0;
  virtual ~Item();
};

#endif
