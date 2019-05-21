#ifndef _CELL_H_
#define _CELL_H_
#include <iostream>
#include <vector>
#include <utility>

class Cell {
protected:
    int row;
    int col;
    char symbol;
    std::string type;
    char prev; // Save the symbol at the original position when moving
public:
    Cell(int r=0, int c=0, char symbol=' ',std::string type="undefined"); // Default constructor
    int getRow();
    int getCol();
    char getSymbol();
    std::string getType();
    void setCood(int r, int c);
    void setType(std::string type);
    void setSymbol(char s);
    void setPrev(char c);
    char getPrev();
    virtual ~Cell();
};


#endif
