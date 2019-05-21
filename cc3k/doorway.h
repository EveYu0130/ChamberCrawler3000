#ifndef _DOORWAY_H_
#define _DOORWAY_H_
#include <iostream>
#include <vector>
#include "cell.h"

class Doorway : public Cell {
public:
    Doorway(int row, int col, char symbol = '+', std::string type = "Doorway");
};

#endif
