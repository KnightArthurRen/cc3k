//
//  view.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__view__
#define __cc3k__view__

#include <iostream>
#include <string>

class View {
    
protected:
    const int rowNum, colNum;
public:
    View(int rowNum, int colNum);
    
    /*
     * The Controller calls notify to
     * update the (r,c) location to be ch
     */
    virtual void notify(int r, int c, char ch) = 0;
    
    virtual void notifyRace(std::string race) = 0;
    virtual void notifyGold(int gold) = 0;
    virtual void notifyHP(int HP) = 0;
    virtual void notifyAtk(int Atk) = 0;
    virtual void notifyDef(int Def) = 0;
    virtual void notifyAction(std::string action) = 0;
    virtual void notifyFloor(char floor) = 0;
    
    virtual void print(std::ostream &out) = 0;
    
    virtual ~View() = 0;
};

#endif /* defined(__cc3k__view__) */
