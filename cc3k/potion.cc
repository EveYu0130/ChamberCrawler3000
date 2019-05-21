#include "potion.h"
#include <string>
using namespace std;

Potion::Potion(int row, int col, bool obtainable, char symbol, string type)
 : Item{row, col, symbol, type, obtainable} {}

bool Potion::getPositive() const { return isPositive; }

bool Potion::getUsed() const { return isUsed; }

bool Potion::getPerm() const { return isPerm; }

string Potion::getPotName() const { return potName; }


void Potion::setPositive(bool isPos) { isPositive = isPos; }

void Potion::setUsed(bool isUsed) { isUsed = isUsed; }

void Potion::setPerm(bool isPerm) { isPerm = isPerm; }
