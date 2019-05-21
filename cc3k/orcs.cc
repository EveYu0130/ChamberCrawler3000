#include "orcs.h"
#include "player.h"
#include <cstdlib>
using namespace std;

Orcs::Orcs(int row, int col, Floor *f, char symbol, string type)
:Enemy{row, col, f, symbol, type} {
  hp = 180;
  atk = 30;
  def = 25;
  int i = rand() % 2;
  if (i) golddrop = 1;
  else golddrop = 2;
  hostile = true;
  abletomove = true;
}

void Orcs::attack(Player &p) {
  if (hostile && !freezed) p.defense(*this);
}
