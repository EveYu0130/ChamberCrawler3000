#include "character.h"
using namespace std;

// test comment
Character::Character(int row, int col, Floor *f, char symbol, string type)
: Cell{row, col, symbol, type}, f{f} {}

int Character::getatk() { return atk; }

int Character::getdef() { return def; }

int Character::gethp() { return hp; }

Floor *Character::getfloor() { return f; }

void Character::update(int hpchange, int atkchange, int defchange) {
  hp = hp+hpchange < 0? 0 : hp+hpchange;
  atk = atk+atkchange < 0? 0 : atk+atkchange;
  def = def+defchange < 0? 0 : def + defchange;
}
