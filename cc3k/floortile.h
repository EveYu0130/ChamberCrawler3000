#ifndef _FLOORTILE_H_
#define _FLOORTILE_H_
#include <iostream>
#include <vector>
#include "cell.h"

class FloorTile : public Cell {
public:
    FloorTile(int row, int col, char symbol = '.', std::string type = "FloorTile");
};

#endif
