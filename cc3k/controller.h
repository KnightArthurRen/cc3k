//
//  controller.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__controller__
#define __cc3k__controller__

#include <iostream>
#include <string>
#include "game.h"
#include "cell.h"
#include "view.h"

// More documentation in controller.cc file

class Controller : public GameNotification {
    
    View *td; // The text display.
    //    View *gd; // The graphic display.
    
    Game *game;
    
    static const int rowNum;
    static const int colNum;
    
    void init(std::istream & input, Game & g);
    
    
public:
    Controller();
    ~Controller();
    
    // return true if needs to restart, false otherwise
    bool play(const char *file = NULL);
    
    void notify(int r, int c, char state);
    void notifyRace(std::string race);
    void notifyGold(int gold);
    void notifyHP(int HP);
    void notifyAtk(int Atk);
    void notifyDef(int Def);
    void notifyAction(std::string action);
    void notifyFloor(char floor);
};

#endif /* defined(__cc3k__controller__) */
