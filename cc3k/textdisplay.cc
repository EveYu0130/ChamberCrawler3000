#include <iostream>
#include <utility>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(): length{79}, width{25} {
    theDisplay.assign(width, vector<char>(length, ' '));
}


TextDisplay::~TextDisplay() {
    theDisplay.clear();
}

void TextDisplay::notify(int r, int c, char sym) {
    theDisplay[r][c] = sym;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (int row = 0; row < td.width; ++row) {
        for (int col = 0; col < td.length; ++col) {
            out << td.theDisplay[row][col];
        }
        out << endl;
    }
  return out;
}
