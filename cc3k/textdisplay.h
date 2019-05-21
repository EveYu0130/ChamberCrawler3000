#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>

class TextDisplay {
    std::vector<std::vector<char>> theDisplay;
    int length;
    int width;
public:
    TextDisplay();
    void notify(int r, int c, char sym);
    ~TextDisplay();

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
