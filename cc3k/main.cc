#include "floor.h"
#include "player.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {
 	bool newGame = true;
  	bool endGame = false;
  	bool invalidCommand = false;
  	bool resetGame = false;
  	string fileName;
  	string race = "s";
  	int seed = time(NULL);
  	cin.exceptions(ios::eofbit|ios::failbit);
  	if(argc == 3) {
  		newGame = false;
  		fileName = argv[1];
      		istringstream ss{argv[2]};
  		ss >> seed;
  	}
  	else if(argc == 2) {
  		newGame = false;
  		fileName = argv[1];
  	}
  	if(newGame) {
  		cout << "Welcome to CC3K! Please choose a race from the following:" << endl;
  		cout << "Shade(s)  Drow(d)  Vampire(v)  Goblin(g)  Troll(t)" << endl;
  		cout << "Or enter (q) to quit." << endl;
  		while(true) {
  			cin >> race;
  	  		if(race == "q") {
  		  		endGame = true;
  		  		break;
  	  		}
  	  		else if (race == "s") {
				race = "Shade";
				break;
			} else if(race == "d") {
				race = "Drow";
				break;
			} else if (race == "v") {
				race = "Vampire";
				break;
			} else if (race == "g") {
				race = "Goblin";
				break;
			} else if (race == "t") {
  	  			race = "Troll";
				break;
  	  		}
  	  		else {
  	  			cout << "Please enter a valid race." << endl;
  	  		}
	    	}
  	}

  	srand(seed);
	Floor f;
    	if(!newGame && !endGame) {
		f.loadMap(fileName);
        f.generateEnemies();
    	}
    	else if(newGame && !endGame) {
    		f.init();
		f.generatePlayer(race);
    		f.generate();
		cout << "A new game begins!" << endl;
    	}
    	Player *p = f.getPlayer();

	if(!endGame && p->isAlive() && f.getLevel() != 6) {
		cout << f;
		cout << "Race: " << p->getType() << " Gold: " << p->getgold() << "                                              Floor " << f.getLevel() << endl;
		cout << "HP: " << p->gethp() << endl;
		cout << "Atk: " << p->getatk() << endl;
		cout << "Def: " << p->getdef() << endl;
		cout << "Action: Player character has spawned." << endl;
	}
    	while(!endGame && p->isAlive() && f.getLevel() != 6) {
			bool isFrozen = false;
   			string command;
   			string direction;

   			cin >> command;

   			if(command == "f") {
   				f.freezed();
   				if(!isFrozen) {
   					f.actionAppend("Enemies have been frozen. Enter (f) again to unfreeze.");
   					isFrozen = true;
   				}
   				else {
   					f.actionAppend("Enemies have been unfrozen.");
   					isFrozen = false;
   				}
   			}
   			else if(command == "r") {
				f.init();

				cout << "Welcome to CC3K! Please choose a race from the following:" << endl;
  				cout << "Shade(s)  Drow(d)  Vampire(v)  Goblin(g)  Troll(t)" << endl;
  				cout << "Or enter (q) to quit." << endl;
  				while(true) {
  					cin >> race;
  	  				if(race == "q") {
  		  				endGame = true;
  		  				break;
  	  				}
  	  				else if (race == "s") {
						race = "Shade";
						break;
					}
					else if (race == "d") {
						race = "Drow";
						break;
					}
					else if (race == "v") {
						race = "Vampire";
						break;
					}
					else if (race == "g") {
						race = "Goblin";
						break;
					}
					else if (race == "t") {
						race == "Troll";
  	  					break;
  	  				}
  	  				else {
  	  					cout << "Please enter a valid race." << endl;
  	  				}
    			}
				f.generatePlayer(race);
				f.generate();
	   			p = f.getPlayer();
				cout << "A new game begins! " << endl;
				cout << f;
				cout << "Race: " << p->getType() << " Gold: " << p->getgold() << "                                              Floor " << f.getLevel() << endl;
				cout << "HP: " << p->gethp() << endl;
				cout << "Atk: " << p->getatk() << endl;
				cout << "Def: " << p->getdef() << endl;
				cout << "Action: Player character has spawned." << endl;
				resetGame = true;
   			}
   			else if(command == "q") {
   				endGame = true;
   			}
   			else if(command == "no" || command == "so" || command == "ea" || command == "we" || command == "ne" || command == "nw" || command == "se" || command == "sw") {
				p->move(command);
   				f.allEnemiesMoveAttack();
      		}

   			else if(command == "u") {
   				cin >> direction;
   				if(direction == "no" || direction == "so" || direction == "ea" || direction == "we" || direction == "ne" || direction == "nw" || direction == "se" || direction == "sw") {
   					p->usePotion(direction);
   					f.allEnemiesMoveAttack();
   				}
   			}
   			else if(command == "a") {
   				cin >> direction;
   				if(direction == "no" || direction == "so" || direction == "ea" || direction == "we" || direction == "ne" || direction == "nw" || direction == "se" || direction == "sw") {
   					p->attackInDirection(direction);
   					f.allEnemiesMoveAttack();
   				}
   			}
   			else {
   				cout << "Please enter a valid command" << endl;
   				invalidCommand = true;
   			}
   			if(!invalidCommand && f.getLevel() != 6 && !resetGame) {
				cout << f;
				cout << "Race: " << p->getType() << " Gold: " << p->getgold() << "                                                 Floor: " << f.getLevel() << endl;
				cout << "HP: " << p->gethp() << endl;
				cout << "Atk: " << p->getatk() << endl;
				cout << "Def: " << p->getdef() << endl;
				cout << "Action: " << f.getAction() << endl;
				f.clearAction();
			}
			invalidCommand = false;
			resetGame = false;
			if(f.getLevel() == 6) break;
			if(p->getType() == "Troll") {
				p->update(5, 0, 0);
			}
   	 	}
       	if(p && !p->isAlive()) {
    		cout << "Player had died." << endl;
    	}
    	if(f.getLevel() == 6) {
    		double score = p->getgold();
    		if(p->getType() == "Shade") {
    			score = score * 1.5;
    		}
    		cout << "Your final score: " << score << "." << endl;
    	}
    	cout << "Thank you for playing CC3K!" << endl;
}
