#ifndef _PASSAGE_H_
#define _PASSAGE_H_
#include <iostream>
#include <vector>
#include "cell.h"

class Passage : public Cell {
public:
    Passage(int row, int col, char symbol = '#', std::string type = "Passage");
};

#endif
