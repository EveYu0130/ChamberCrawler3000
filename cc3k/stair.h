#ifndef _STAIR_H_
#define _STAIR_H_
#include <iostream>
#include <vector>
#include "cell.h"

class Stair : public Cell {
public:
    Stair(int row, int col, char symbol = '\\', std::string type = "Stair");
};

#endif
