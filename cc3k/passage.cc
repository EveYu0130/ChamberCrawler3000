#include "passage.h"

Passage::Passage(int row, int col, char symbol, std::string type):
    Cell{row, col, symbol, type} {}
