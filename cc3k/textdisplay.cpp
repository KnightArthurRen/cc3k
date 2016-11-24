//
//  textdisplay.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "textdisplay.h"
#include <iomanip>
#include <sstream>

using namespace std;

TextDisplay::TextDisplay(int rowNum, int colNum) : View(rowNum, colNum) {
    theDisplay = new char*[rowNum];
    for (int i = 0; i < rowNum; ++i) {
        theDisplay[i] = new char[colNum];
        for (int j = 0; j < colNum; ++j) {
            // default is a single space
            theDisplay[i][j] = ' ';
        } // for
    } // for
    race = "Shade";
    gold = 0;
    action = "";
    floor = '1';
} // constructor


TextDisplay::~TextDisplay() {
    for (int i = 0; i < rowNum; ++i) {
        delete [] theDisplay[i];
    } // for
    delete [] theDisplay;
} // destructor


void TextDisplay::notify(int r, int c, char ch) {
    theDisplay[r][c] = ch;
    return;
} // notify


void TextDisplay::notifyRace(string race) {
    this->race = race;
} // notifyRace


void TextDisplay::notifyGold(int gold) {
    this->gold = gold;
} // notifyGold


void TextDisplay::notifyHP(int HP) {
    this->HP = HP;
} // notifyHP


void TextDisplay::notifyAtk(int Atk) {
    this->Atk = Atk;
} // notifyAtk


void TextDisplay::notifyDef(int Def) {
    this->Def = Def;
} // notifyDef


void TextDisplay::notifyAction(string action) {
    // if being notified by an empty message, then ignore
    if (action.length() == 0) {
        return;
    } // if
    
    if (this->action.length() != 0) {
        this->action += " " + action;
    } else {
        this->action += action;
    } // if, else
} // notifyAction


void TextDisplay::notifyFloor(char floor) {
    this->floor = floor;
} // notifyFloor


void TextDisplay::print(std::ostream &out) {
    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            out<<theDisplay[i][j];
        } // for
        out<<endl;
    } // for
    string line = "Race: " + race + " Gold: ";
    stringstream stream;
    stream<<gold;
    string numStr;
    stream>>numStr;
    line += numStr;
    out<<setfill(' ')<<left<<setw(69)<<line<<"Floor "<<floor<<endl;
    out<<"HP: "<<HP<<endl<<"Atk: "<<Atk<<endl<<"Def: "<<Def<<endl;
    out<<"Action: "<<action<<endl;
    action.clear();     // clear the actions
} // print