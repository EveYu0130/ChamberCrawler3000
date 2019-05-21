#ifndef _HWALL_H_
#define _HWALL_H_
#include <iostream>
#include <vector>
#include "cell.h"

class Hwall : public Cell {
public:
    Hwall(int row, int col, char symbol = '-', std::string type = "Hwall");
};

#endif
