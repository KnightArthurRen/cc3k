//
//  controller.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include <fstream>
#include <cstdlib>
#include "controller.h"
#include "textdisplay.h"

using namespace std;

const int Controller::rowNum = 25;
const int Controller::colNum = 79;

Controller::Controller(){
    game = new Game();
    td = NULL;
} // default ctor


/*
 * Update the View(s) to indicate the new game state
 */
void Controller::notify(int r, int c, char state) {
    td->notify(r, c, state);
} // notify


void Controller::notifyRace(string race) {
    td->notifyRace(race);
} // notifyRace


void Controller::notifyGold(int gold) {
    td->notifyGold(gold);
} // notifyGold


void Controller::notifyHP(int HP) {
    td->notifyHP(HP);
} // notifyHP


void Controller::notifyAtk(int Atk) {
    td->notifyAtk(Atk);
} // notifyAtk


void Controller::notifyDef(int Def) {
    td->notifyDef(Def);
} // notifyDef


void Controller::notifyAction(string action) {
    td->notifyAction(action);
} // notifyAction


void Controller::notifyFloor(char floor) {
    td->notifyFloor(floor);
} // notifyFloor


/*
 * Called when initializing a new floor
 */
void Controller::init(istream & input, Game &g){
    input.clear();
    string line;
    const int maxRow = 25;
    const int maxCol = 79;
    int row = 0, col = 0;
    // get rid of leading whitespaces
    while (isspace(input.peek())) {
        input.ignore();
    } // while
    
    // loop only exit on reading in EOF or reaching maxRow
    while (getline(input, line)) {
#ifdef DEBUG
        cout<<"Getting line number "<<row<<endl;
#endif
#ifdef DEBUG
        if (line == "END") {
            break;
        } // exit
#endif
        for (string::iterator it = line.begin(); it < line.end(); ++it) {
            g.init(row, col, *it);
            ++col;
            if (col >= maxCol) {
                ++row;
                col = 0;
            } // if
        } // for
        if (row >= maxRow) {
            break;
        } // if
    } // while
} // init


bool Controller::play(const char *file){
    // use current time as seed for random generator
    srand(static_cast<unsigned>(time(0)));
    
    delete td;
    td = new TextDisplay(rowNum, colNum);
    game->init(this);
    game->resetPotionMerchant();

    string cmd;
    cout<<"Choose your race now, or (q)uit!"<<endl;
    
    // loop only exit when user enters a valid race
    while(cin>>cmd) {
        // set pc's race according to cmd
        if (cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" || cmd == "t") {
            game->chooseRace(cmd.at(0));
            cout<<"Smart pick!"<<endl;
            break;
        } // exit
        
        if (cmd == "q") {
            return false;
        } // exit
        cout<<"Wow! That's not a valid race!"<<endl;
    } // while
    
    
    ifstream fin;
#ifdef DEBUG
    cout<< "Begin initialization"<<endl;
#endif
    if (file != NULL) {
#ifdef DEBUG
        cout<<"constructing fin"<<endl;
#endif
        fin.open(file);
        init(fin, *game);
#ifdef DEBUG
        cout << "Done file initialization" << endl;
#endif
    } else {
        init(cin, *game);
#ifdef DEBUG
        cout<<"Done initialization"<<endl;
#endif
    } // if, else
    
    cout<<"The Game Begins Now"<<endl;
    game->scanPotion();
    td->print(cout);
    
    while (cin>>cmd) {
        
        // player movement
        if (cmd=="no" || cmd=="so" || cmd=="ea" || cmd=="we" || cmd=="ne" || cmd=="nw" || cmd=="se" || cmd=="sw") {
            if(game->playerMove(cmd) == false) {
                cout<<"Invalid movement!"<<endl;
                continue;
            } // if
            
            if (game->isWon() == true) {
                cout<<"Congratulations, you win! You escaped the dungeon!"<<endl;
                cout<<"Your score is "<<game->getScore()<<endl;
                return true;
            } // exit
            
            // if switched floor, then init, else endturn
            if (game->isFloorChanged() == true) {
                game->init(this);
                if (file != NULL) {
                    init(fin, *game);
                } else {
                    init(cin, *game);
                } // if, else
                game->scanPotion();
            } else {
                game->endTurn();
            }
            td->print(cout);
        } // if
        
        // player attack
        if (cmd == "a") {
            cin >> cmd;
            if (cmd=="no" || cmd=="so" || cmd=="ea" || cmd=="we" || cmd=="ne" || cmd=="nw" || cmd=="se" || cmd=="sw") {
                if(game->playerAtk(cmd) == false) {
                    cout<<"Invalid attack!"<<endl;
                    continue;
                } // if
                game->endTurn();
                td->print(cout);
            } else {
                cout<<"Invalid attack!"<<endl;
                continue;
            } // if, else
        } // if
        
        // use potion
        if (cmd == "u") {
            cin >> cmd;
            if (cmd=="no" || cmd=="so" || cmd=="ea" || cmd=="we" || cmd=="ne" || cmd=="nw" || cmd=="se" || cmd=="sw") {
                if (game->consumePotion(cmd) == false) {
                    cout<<"Invalid use!"<<endl;
                    continue;
                }
                game->endTurn();
                td->print(cout);
            } else {
                cout<<"Invalid use!"<<endl;
                continue;
            }
        } // if
        
        if (cmd == "r") {
            cout<<"Restarting!"<<endl;
            return true;    // restart
        } // exit
        
        if (cmd == "q") {
            cout<<"You quit!"<<endl;
            return false;
        } // exit
        
        // check if pc is dead
        if (game->isLose() == true) {
            cout<<"You are dead!"<<endl;
            return true;
        } // exit
    }
    
    return false;
} // play


Controller::~Controller(){
    delete  td;
    td = NULL;      // assign NULL to td, prevent potential double delete
    delete game;
    game = NULL;    // assign NULL to game, prevent potential double delete
} // default dtor
