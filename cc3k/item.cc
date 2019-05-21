#include "item.h"
using namespace std;

bool Item::getObtainable() const { return obtainable; }

void Item::setObtainable(bool obtainable) {
	obtainable = obtainable;
	cout << "obtainable is currently " << obtainable << endl; }

Item::Item(int row, int col, char symbol, string type, bool obtainable)
: Cell{row, col, symbol, type}, obtainable{obtainable} {}

Item::~Item() {}
