#include "floor.h"
#include "stair.h"
#include "passage.h"
#include "hwall.h"
#include "vwall.h"
#include "doorway.h"
#include "floortile.h"
#include "enemy.h"
#include "treasure.h"
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orcs.h"
#include "merchant.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "pothp.h"
#include "potatk.h"
#include "potdef.h"
#include "dragon.h"

using namespace std;

Floor::Floor()
     : length{79}, width{25}, td{nullptr}, level{1}, p{nullptr} { action = "Player has spawned. ";}

Floor::~Floor() {
    clearFloor();
}

void Floor::actionAppend(string act) {
	string temp = action + act;
	action = temp;
}

string Floor::getAction() {return action;}

void Floor::clearAction() {action = "";}

void Floor::loadMap(std::string textMap) {
    clearFloor();
    td = new TextDisplay{};
    map.assign(width, vector<Cell*>(length, nullptr));
    for (int row = 0; row < width; ++row) {
        for (int col = 0; col < length; ++col) {
            map[row][col] = new Cell{row,col};
        }
    }
    ifstream infile;
    infile.open(textMap);
    for (int r = 0; r < width; ++r) {
        string line;
        getline(infile, line);
        istringstream iss{line};
        int c = 0;
        char sym;
        while (iss >> noskipws >> sym) {
            if (sym == '-') {
                delete map[r][c];
                map[r][c] = new Hwall{r,c};
            }
            if (sym == '|') {
                delete map[r][c];
                map[r][c] = new Vwall{r,c};
            }
            if (sym == '+') {
                delete map[r][c];
                map[r][c] = new Doorway{r,c};
            }
            if (sym == '#') {
                delete map[r][c];
                map[r][c] = new Passage{r,c};
            }
            if (sym == '.') {
                delete map[r][c];
                map[r][c] = new FloorTile{r,c};
            }
            if (sym == '0') {
                delete map[r][c];
                map[r][c] = new PotHP{r,c,true};
            }
            if (sym == '1') {
                delete map[r][c];
                map[r][c] = new PotATK{r,c,true};
            }
            if (sym == '2') {
                delete map[r][c];
                map[r][c] = new PotDEF{r,c,true};
            }
            if (sym == '3') {
                delete map[r][c];
                map[r][c] = new PotHP{r,c,false};
            }
            if (sym == '4') {
                delete map[r][c];
                map[r][c] = new PotATK{r,c,false};
            }

            if (sym == '5') {
                delete map[r][c];
                map[r][c] = new PotDEF{r,c,false};
            }
            if (sym == '6') {
                delete map[r][c];
                map[r][c] = new Treasure{r,c,true,1};
            }
            if (sym == '7') {
                delete map[r][c];
                map[r][c] = new Treasure{r,c,true,2};
            }
            if (sym == '8') {
                delete map[r][c];
                map[r][c] = new Treasure{r,c,false,4};
            }
            if (sym == '9') {
                delete map[r][c];
                map[r][c] = new Treasure{r,c,false,6};
            }
            if (sym == '@') {
                delete map[r][c];
                p = new Shade{r,c,this};
                map[r][c] = p;
            }
            if (sym == '\\') {
                delete map[r][c];
                map[r][c] = new Stair{r,c};
            }
            ++c;
        }
    }
    for (int row = 0; row < width; ++row) {
        for (int col = 0; col < length; ++col) {
            char sym = map[row][col]->getSymbol();
            if (sym != ' ') {
                int r = map[row][col]->getRow();
                int c = map[row][col]->getCol();
                td->notify(r,c,sym);
            }
        }
    }
}
void Floor::init() {
    clearFloor();
    td = new TextDisplay{};
    map.assign(width, vector<Cell*>(length, nullptr));
    for (int row = 0; row < width; ++row) {
        for (int col = 0; col < length; ++col) {
            map[row][col] = new Cell{row,col};
        }
    }

    // initialize the top line and bottom line to -
    for (int col = 1; col < length-1; ++col) {
        delete map[0][col];
        map[0][col] = new Hwall{0,col};
        delete map[24][col];
        map[24][col] = new Hwall{24,col};
    }

    // initialize the top left and top right line to |
    for (int row = 0; row < width; ++row) {
        delete map[row][0];
        map[row][0] = new Vwall{row,0};
        delete map[row][78];
        map[row][78] = new Vwall{row,78};
    }


    // initialize the first chamber
    for (int col = 3; col < 29; ++col) {
        delete map[2][col];
        map[2][col] = new Hwall{2,col};
        delete map[7][col];
        map[7][col] = new Hwall{7,col};
    }
    for (int row = 2; row < 8; ++row) {
        delete map[row][2];
        map[row][2] = new Vwall{row,2};
        delete map[row][29];
        map[row][29] = new Vwall{row,29};
    }
    for (int row = 3; row < 7; ++row) {
        for (int col = 3; col < 29; ++col) {
            delete map[row][col];
            map[row][col] = new FloorTile{row,col};
        }
    }
    delete map[4][29];
    map[4][29] = new Doorway{4,29};
    delete map[7][13];
    map[7][13] = new Doorway{7,13};


    // initialize the second chamber
    for (int col = 4; col < 25; ++col) {
        delete map[14][col];
        map[14][col] = new Hwall{14,col};
        delete map[22][col];
        map[22][col] = new Hwall{22,col};
    }
    for (int row = 14; row < 23; ++row) {
        delete map[row][3];
        map[row][3] = new Vwall{row,3};
        delete map[row][25];
        map[row][25] = new Vwall{row,25};
    }
    for (int row = 15; row < 22; ++row) {
        for (int col = 4; col < 25; ++col) {
            delete map[row][col];
            map[row][col] = new FloorTile{row,col};
        }
    }
    delete map[14][13];
    map[14][13] = new Doorway{14,13};
    delete map[20][25];
    map[20][25] = new Doorway{20,25};



    // initialize the third chamber
    for (int col = 38; col < 50; ++col) {
        delete map[9][col];
        map[9][col] = new Hwall{9,col};
        delete map[13][col];
        map[13][col] = new Hwall{13,col};
    }
    for (int row = 9; row < 14; ++row) {
        delete map[row][37];
        map[row][37] = new Vwall{row,37};
        delete map[row][50];
        map[row][50] = new Vwall{row,50};
    }
    for (int row = 10; row < 13; ++row) {
        for (int col = 38; col < 50; ++col) {
            delete map[row][col];
            map[row][col] = new FloorTile{row,col};
        }
    }
    delete map[9][43];
    map[9][43] = new Doorway{9,43};
    delete map[13][43];
    map[13][43] = new Doorway{13,43};



    // initialize the forth chamber
    for (int col = 39; col < 62; ++col) {
        delete map[2][col];
        map[2][col] = new Hwall{2,col};
    }
    for (int col = 63; col < 70; ++col) {
        delete map[4][col];
        map[4][col] = new Hwall{4,col};
    }
    for (int col = 71; col < 73; ++col) {
        delete map[5][col];
        map[5][col] = new Hwall{5,col};
    }
    for (int col = 74; col < 76; ++col) {
        delete map[6][col];
        map[6][col] = new Hwall{6,col};
    }
    for (int col = 39; col < 60; ++col) {
        delete map[7][col];
        map[7][col] = new Hwall{7,col};
    }
    for (int col = 61; col < 76; ++col) {
        delete map[13][col];
        map[13][col] = new Hwall{13,col};
    }
    for (int row = 2; row < 8; ++row) {
        delete map[row][38];
        map[row][38] = new Vwall{row,38};
    }
    for (int row = 2; row < 5; ++row) {
        delete map[row][62];
        map[row][62] = new Vwall{row,62};
    }
    for (int row = 4; row < 6; ++row) {
        delete map[row][70];
        map[row][70] = new Vwall{row,70};
    }
    for (int row = 5; row < 7; ++row) {
        delete map[row][73];
        map[row][73] = new Vwall{row,73};
    }
    for (int row = 6; row < 14; ++row) {
        delete map[row][76];
        map[row][76] = new Vwall{row,76};
    }
    for (int row = 7; row < 14; ++row) {
        delete map[row][60];
        map[row][60] = new Vwall{row,60};
    }
    for (int row = 3; row < 5; ++row) {
        for (int col = 39; col < 62; ++col) {
            delete map[row][col];
            map[row][col] = new FloorTile{row,col};
        }
    }
    for (int col = 39; col < 70; ++col) {
        delete map[5][col];
        map[5][col] = new FloorTile{5,col};
    }
    for (int col = 39; col < 73; ++col) {
        delete map[6][col];
        map[6][col] = new FloorTile{6,col};
    }
    for (int row = 7; row < 13; ++row) {
        for (int col = 61; col < 76; ++col) {
            delete map[row][col];
            map[row][col] = new FloorTile{row,col};
        }
    }
    delete map[4][38];
    map[4][38] = new Doorway{4,38};
    delete map[7][43];
    map[7][43] = new Doorway{7,43};
    delete map[11][60];
    map[11][60] = new Doorway{11,60};
    delete map[13][69];
    map[13][69] = new Doorway{13,69};



    // initialize the fifth chamber
    for (int col = 65; col < 76; ++col) {
        delete map[15][col];
        map[15][col] = new Hwall{15,col};
    }
    for (int col = 37; col < 76; ++col) {
        delete map[22][col];
        map[22][col] = new Hwall{22,col};
    }
    for (int col = 37; col < 64; ++col) {
	delete map[18][col];
	map[18][col] = new Hwall{18,col};
    }
    for (int row = 15; row < 19; ++row) {
        delete map[row][64];
        map[row][64] = new Vwall{row,64};
    }
    for (int row = 18; row < 23; ++row) {
        delete map[row][36];
        map[row][36] = new Vwall{row,36};
    }
    for (int row = 15; row < 23; ++row) {
        delete map[row][76];
        map[row][76] = new Vwall{row,76};
    }
    for (int row = 16; row < 19; ++row) {
        for (int col = 65; col < 76; ++col) {
            delete map[row][col];
            map[row][col] = new FloorTile{row,col};
        }
    }
    for (int row = 19; row < 22; ++row) {
        for (int col = 37; col < 76; ++col) {
            delete map[row][col];
            map[row][col] = new FloorTile{row,col};
        }
    }
    delete map[15][69];
    map[15][69] = new Doorway{15,69};
    delete map[18][43];
    map[18][43] = new Doorway{18,43};
    delete map[20][36];
    map[20][36] = new Doorway{20,36};



    // initialize the passages
    for (int col = 30; col < 38; ++col) {
        delete map[4][col];
        map[4][col] = new Passage{4,col};
    }
    for (int col = 31; col < 44; ++col) {
        delete map[8][col];
        map[8][col] = new Passage{8,col};
    }
    for (int col = 13; col < 32; ++col) {
        delete map[11][col];
        map[11][col] = new Passage{11,col};
    }
    for (int col = 54; col < 60; ++col) {
        delete map[11][col];
        map[11][col] = new Passage{11,col};
    }
    for (int col = 31; col < 55; ++col) {
        delete map[16][col];
        map[16][col] = new Passage{16,col};
    }
    for (int col = 26; col < 36; ++col) {
        delete map[20][col];
        map[20][col] = new Passage{20,col};
    }
    for (int row = 8; row < 14; ++row) {
        delete map[row][13];
        map[row][13] = new Passage{row,13};
    }
    for (int row = 5; row < 8; ++row) {
        delete map[row][33];
        map[row][33] = new Passage{row,33};
    }
    for (int row = 9; row < 20; ++row) {
        delete map[row][31];
        map[row][31] = new Passage{row,31};
    }
    for (int row = 14; row < 18; ++row) {
        delete map[row][43];
        map[row][43] = new Passage{row,43};
    }
    for (int row = 12; row < 16; ++row) {
        delete map[row][54];
        map[row][54] = new Passage{row,54};
    }
    delete map[14][69];
    map[14][69] = new Passage{14,69};



    for (int row = 0; row < width; ++row) {
        for (int col = 0; col < length; ++col) {
            char sym = map[row][col]->getSymbol();
            if (sym != ' ') {
                int r = map[row][col]->getRow();
                int c = map[row][col]->getCol();
                td->notify(r,c,sym);
            }
        }
    }

}

void Floor::removeEnemy() {
	enemies.clear();
    for (int row = 0; row < width; ++row) {
        for (int col = 0; col < length; ++col) {
            char sym = map[row][col]->getSymbol();
            if ((sym == 'D') || (sym == 'M') || (sym == 'O') || (sym == 'E') ||
                (sym == 'W') || (sym == 'L') || (sym == 'H')) {
                delete map[row][col];
                map[row][col] = new FloorTile{row, col};
                td->notify(row,col,'.');
            }
        }
    }
}


void Floor::removeEntity() {
	enemies.clear();
    for (int row = 0; row < width; ++row) {
        for (int col = 0; col < length; ++col) {
            if (map[row][col]->getPrev() == '.') {
                delete map[row][col];
                map[row][col] = new FloorTile{row, col};
                td->notify(row,col,'.');
            };
        }
    }
}

void Floor::clearFloor() {
    for (auto row : map) {
        for (auto cell : row) {
            delete cell;
        }
    }
    map.clear();
    delete td;
}

int Floor::getLevel() {
    return level;
}

Cell *Floor::getCell(int r, int c) {
	return map[r][c];
}



void Floor::moveUp() {
    if (level != 5) {
        ++level;
        removeEntity();
        resetPlayer();
        generate();
    }
    else {
        ++level;
	}
}

void Floor::resetPlayer() {
    int pc_r = p->getRow();
    int pc_c = p->getCol();
    int new_chamber = rand() % 5 + 1;
    Cell *orig = generateCell(new_chamber);
    int r = orig->getRow();
    int c = orig->getCol();
    delete orig;
    if (pc_r != r || pc_c != c) {
    	map[pc_r][pc_c] = new FloorTile{pc_r,pc_c};
    	td->notify(pc_r,pc_c,'.');
    }
    map[r][c] = p;
    p->setCood(r,c);
    td->notify(r,c,'@');
    p->setPrev('.');
    p->setnextfloor();
}

Cell *Floor::generateCell(int chamber) {
    int r;
    int c;
    if (chamber == 1) {
        r = rand() % 4 + 3;
        c = rand() % 26 + 3;
    } else if (chamber  == 2) {
        r = rand() % 7 + 15;
        c = rand() % 21 + 4;
    } else if (chamber  == 3) {
        r = rand() % 3 + 10;
        c = rand() % 12 + 38;
    } else if (chamber == 4) {
        r = rand() % 10 + 3;
        c = rand() % 37 + 39;
        while ( (r >= 7 && r <= 12 && c >= 39 && c <= 60) ||
                (r >= 3 && r <=4 && c >= 62 && c <= 75) ||
                (r == 5 && c >= 70 && c <= 75) ||
                (r == 6 && c >= 73 && c <= 75)) {
                    r = rand() % 10 + 3;
                    c = rand() % 37 + 39;
                }
    } else { // chamber == 5
        r = rand() % 6 + 16;
        c = rand() % 39 + 37;
        while (r >= 16 && r <= 18 && c >= 37 && c <= 64) {
            r = rand() % 6 + 16;
            c = rand() % 39 + 37;
        }
    }
    return map[r][c];
}


int pc_chamber;

void Floor::generatePlayer(std::string race) {
    pc_chamber = rand() % 5 + 1;
    Cell *orig = generateCell(pc_chamber);
    int r = orig->getRow();
    int c = orig->getCol();
    char sym = orig->getSymbol();
    delete orig;
    if (race == "Shade") {
	p = new Shade{r,c,this};
    }
    if (race == "Drow") p = new Drow{r,c,this};
    if (race == "Vampire") p = new Vampire{r,c,this};
    if (race == "Troll") p = new Troll{r,c,this};
    if (race == "Goblin") p = new Goblin{r,c,this};
    p->setPrev(sym);
    map[r][c] = p;
    td->notify(r,c,'@');
}

Player *Floor::getPlayer() {
    return this->p;
}


void Floor::generate() {
    generateStair();
    generatePotions();
    generateGolds();
    generateEnemies();
}

void Floor::generateStair() {
    int stair_chamber = rand() % 5 + 1;
    while (stair_chamber == pc_chamber) {
        stair_chamber = rand() % 5 + 1;
    }
    Cell *orig = generateCell(stair_chamber);
    int r = orig->getRow();
    int c = orig->getCol();
    delete orig;
    map[r][c] = new Stair{r,c};
    td->notify(r,c,'\\');
}

ostream &operator<<(ostream &out, const Floor &f) {
    out << *(f.td);
    return out;
}

Cell *Floor::generateEnemyOrItem() {
    int en_chamber = rand() % 5 + 1;
    Cell *en = generateCell(en_chamber);
    while (en->getSymbol() != '.') {
        en_chamber = rand() % 5 + 1;
        en = generateCell(en_chamber);
    }
    return en;
}

void Floor::generateEnemies() {
    enemies.assign(20, nullptr);
    for (int i = 0; i < 20; i++) {
        Cell *orig = generateEnemyOrItem();
        int r = orig->getRow();
        int c = orig->getCol();
        delete orig;
        int enRace = rand() % 18;
        if (enRace < 4) {
            Enemy *en = new Human{r,c,this};
            map[r][c] = en;
            enemies[i] = en;
        }
        else if (enRace < 7) {
            Enemy *en = new Dwarf{r,c,this};
            map[r][c] = en;
            enemies[i] = en;
        }
        else if ( enRace < 12) {
            Enemy *en = new Halfling{r,c,this};
            map[r][c] = en;
            enemies[i] = en;
        }
        else if ( enRace < 14) {
            Enemy *en = new Elf{r,c,this};
            map[r][c] = en;
            enemies[i] = en;
        }
        else if ( enRace < 16) {
            Enemy *en = new Orcs{r,c,this};
            map[r][c] = en;
            enemies[i] = en;
        }
        else {
            Enemy *en = new Merchant{r,c,this};
            map[r][c] = en;
            enemies[i] = en;
        }
        map[r][c]->setPrev('.');
        char s = map[r][c]->getSymbol();
        td->notify(r,c,s);
    }
}

void Floor::generatePotions() {
    for ( int i = 0; i < 10; i++) {
        Cell *orig = generateEnemyOrItem();
        int r = orig->getRow();
        int c = orig->getCol();
        char sym = orig->getSymbol();
        delete orig;
        int po = rand() % 6;
        if (po == 0) map[r][c] = new PotHP{r,c,true};
        if (po == 1) map[r][c] = new PotATK{r,c,true};
        if (po == 2) map[r][c] = new PotDEF{r,c,true};
        if (po == 3) map[r][c] = new PotHP{r,c,false};
        if (po == 4) map[r][c] = new PotATK{r,c,false};
        if (po == 5) map[r][c] = new PotDEF{r,c,false};
        map[r][c]->setPrev(sym);
        td->notify(r,c,'P');
    }
}


void Floor::generateGolds() {
    for (int i = 0; i < 10; i++) {
        Cell *orig = generateEnemyOrItem();
        int r = orig->getRow();
        int c = orig->getCol();
        char sym = orig->getSymbol();
        delete orig;
        int gold = rand() % 8;
        if (gold < 2) map[r][c] = new Treasure{r,c,true,1};
        else if (gold < 7) map[r][c] = new Treasure{r,c,true,2};
        else { // dragon hoard
            Treasure *tr = new Treasure{r,c,false,6};
            map[r][c] = tr;
            int row = rand() % 3 + (r-1);
            int col = rand() % 3 + (c-1);
            while ((r == row && c == col) || (map[row][col]->getType() != "FloorTile")) {
            	row = rand() % 3 + (r-1);
                col = rand() % 3 + (c-1);
            }
            map[row][col] = new Dragon{row,col,this,tr};
            map[row][col]->setPrev('.');
            td->notify(row,col,'D');
        }
        map[r][c]->setPrev(sym);
        td->notify(r,c,'G');
    }
}

void Floor::allEnemiesMoveAttack() {
    for (auto en : enemies) {
		en->action();
    }
    cout << "finished enemy actions" << endl;
}

void Floor::freezed() {
	int len = enemies.size();
    for (int en = 0; en < len; ++en) {
        enemies[en]->switchfreezed();
    }
}


void Floor::moveCell(Cell *c, int moveToR, int moveToC, bool moveToDH) {
    // valid move is already checked by c
    Cell *orig = map[moveToR][moveToC]; // original cell in desired position
    int currR = c->getRow();
    int currC = c->getCol();
    char sym = orig->getSymbol();
    if (c->getPrev() == 'G') {
        if (map[currR+1][currC]->getType() == "Dragon") {
        	map[currR][currC] = new Treasure{currR,currC,true,6};
        }
        else if (map[currR-1][currC]->getType() == "Dragon") {
        	map[currR][currC] = new Treasure{currR,currC,true,6};
        }
        else if (map[currR+1][currC+1]->getType() == "Dragon") {
        	map[currR][currC] = new Treasure{currR,currC,true,6};
        }
        else if (map[currR-1][currC+1]->getType() == "Dragon") {
        	map[currR][currC] = new Treasure{currR,currC,true,6};
        }
        else if (map[currR+1][currC-1]->getType() == "Dragon") {
        	map[currR][currC] = new Treasure{currR,currC,true,6};
        }
        else if (map[currR-1][currC-1]->getType() == "Dragon") {
        	map[currR][currC] = new Treasure{currR,currC,true,6};
        }
        else if (map[currR][currC+1]->getType() == "Dragon") {
        	map[currR][currC] = new Treasure{currR,currC,true,6};
        }
        else if (map[currR][currC-1]->getType() == "Dragon") {
        	map[currR][currC] = new Treasure{currR,currC,true,6};
        }
        else {
        	map[currR][currC] = new Treasure{currR,currC,false,6};
        }
    }
    else if (c->getPrev() == '+') {
        map[currR][currC] = new Doorway{currR,currC};
    }
    else if (c->getPrev() == '#') {
        map[currR][currC] = new Passage{currR,currC};
    }
    else { // (c->getPrev() == '.')
        map[currR][currC] = new FloorTile{currR,currC};
    }

    char s = map[currR][currC]->getSymbol();
    td->notify(currR,currC,s);
    delete orig;
    c->setCood(moveToR,moveToC);
    if (sym != 'G' || moveToDH) c->setPrev(sym);
    map[moveToR][moveToC] = c;
    td->notify(moveToR,moveToC,c->getSymbol());
}


void Floor::deleteEnOrPo(int r, int c) {
	if (map[r][c]->getType() == "Merchant" || map[r][c]->getType() == "Human") {
		Enemy *e = dynamic_cast<Enemy*>(getCell(r, c));
		Treasure *tr = e->dropTreasure();
		int size = enemies.size();
		for (int i = 0; i < size; ++i) {
			int row = enemies[i]->getRow();
			int col = enemies[i]->getCol();
			if (r == row && c == col) enemies.erase(enemies.begin()+i);
		}
		delete map[r][c];
		map[r][c] = tr;
		td->notify(r,c,'G');
	}
	else {
		int size = enemies.size();
		for (int i = 0; i < size; ++i) {
			int row = enemies[i]->getRow();
			int col = enemies[i]->getCol();
			if (r == row && c == col) enemies.erase(enemies.begin()+i);
		}
		delete map[r][c];
		map[r][c] = new FloorTile{r,c};
		td->notify(r,c,'.');
	}
}
