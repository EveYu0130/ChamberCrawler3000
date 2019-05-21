#include "human.h"
#include "player.h"
#include <cstdlib>
using namespace std;

Human::Human(int row, int col, Floor *f, char symbol, string type)
:Enemy{row, col, f, symbol, type} {
  hp = 140;
  atk = 20;
  def = 20;
  golddrop = 4;
  hostile = true;
  abletomove = true;
}

void Human::attack(Player &p) {
  if (hostile && !freezed) p.defense(*this);
}

