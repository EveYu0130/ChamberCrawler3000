#ifndef _VWALL_H_
#define _VWALL_H_
#include <iostream>
#include <vector>
#include "cell.h"

class Vwall : public Cell {
public:
    Vwall(int row, int col, char symbol = '|', std::string type = "Vwall");
};

#endif
