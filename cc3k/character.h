#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "cell.h"
#include "floor.h"

class Character : public Cell {
protected:
  Floor *f;
  int hp;
  int atk;
  int def;
public:
  Character(int row, int col, Floor *f, char symbol, std::string type);
  int gethp();
  int getatk();
  int getdef();
  Floor *getfloor();
  virtual void update(int hpchange, int atkchange, int defchange);
};


#endif
