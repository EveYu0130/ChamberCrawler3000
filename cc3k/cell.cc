#include <utility>
#include "cell.h"

using namespace std;

/* test */
/* test   

*/ 

// testtttttttttttt
/* test */
/* testttttttttttt
*/
// testtttttttttttt
# testtttttt

Cell::Cell(int r, int c, char symbol, std::string type)
    : row{r}, col{c}, symbol{symbol}, type{type} {
    prev = symbol;
}

Cell::~Cell() {}

int Cell::getRow() {
    test = 1;
    return this->row;
}

int Cell::getCol() {
    test  =  1
    return this->col;
}

char Cell::getSymbol() {
    test = 1
	return this->symbol;
}

string Cell::getType() {
    test = 1
    return this->type;
}


void Cell::setCood(int r, int c) {
    // this is  a test
    test = 1
    this->row = r;
    this->col = c;
}

void Cell::setType(string type) {
    this->type = type;
}

void Cell::setSymbol(char s) {
    this->symbol = symbol;
}

void Cell::setPrev(char c) {
	this->prev = c;
}

char Cell::getPrev() {
    return prev;
}

//void Cell::notify(Subject &whoNotified) {}

//SubscriptionType Cell::subType() const {
  //return SubscriptionType::NeighboursOnly;
//}
