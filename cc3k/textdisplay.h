//
//  textdisplay.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__textdisplay__
#define __cc3k__textdisplay__

#include <iostream>
#include <string>
#include "view.h"

class TextDisplay : public View {
    char **theDisplay;          //the board display
    // PC's infos
    std::string race;
    int gold;
    int HP;
    int Atk;
    int Def;
    char floor;
    // Events happened since last print
    std::string action;
    
public:
    TextDisplay(int rowNum, int colNum); //two arg constructor where the parameters specify size of the board
    
    ~TextDisplay(); //dtor
    
    /*
     * The Controller calls notify to
     * update the (r,c) location to be ch
     */
    virtual void notify(int r, int c, char ch);
    
    virtual void notifyRace(std::string race);
    virtual void notifyGold(int gold);
    virtual void notifyHP(int HP);
    virtual void notifyAtk(int Atk);
    virtual void notifyDef(int Def);
    virtual void notifyAction(std::string action);
    virtual void notifyFloor(char floor);
    
    /*
     * Prints the grid as specified in the assignment specification.
     */
    virtual void print(std::ostream &out);
};

#endif /* defined(__cc3k__textdisplay__) */
