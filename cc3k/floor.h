#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "cell.h"
#include "textdisplay.h"

class Player;
class Enemy;


class Floor {
    std::vector<std::vector<Cell*>> map;
    std::vector<Enemy*> enemies;
    int length;
    int width;
    TextDisplay *td;
    int level;
    Player *p;
    std::string action;

public:
    Floor();
    ~Floor();
    void actionAppend(std::string act);
    std::string getAction();
    void clearAction();
    void init();
    void loadMap(std::string textMap);
    void clearFloor();
    void removeEnemy();
    void removeEntity();
    int getLevel();
    Cell *getCell(int r, int c);
    Player *getPlayer();
    void moveUp();
    void resetPlayer();
    void generate();
    Cell *generateCell(int chamber);
    void generatePlayer(std::string race);
    void generateStair();
    Cell *generateEnemyOrItem();
    void generateEnemies();
    void generatePotions();
    void generateGolds();
    void allEnemiesMoveAttack();
    void freezed();
    void deleteEnOrPo(int r, int c);
    void moveCell(Cell *c, int moveToR, int moveToC, bool moveToDH);

    friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};


#endif
