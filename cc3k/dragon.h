//
//  dragon.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__dragon__
#define __cc3k__dragon__

#include "npc.h"

class DragonHoard;

class Dragon: public NPC {
    static const int Dragon_MaxHP;
    static const int Dragon_Atk;
    static const int Dragon_Def;
    
    DragonHoard *hoard;
    
    void notifyHoard();
    
public:
    Dragon();    // default ctor
    void setHoard(DragonHoard *hoard);
    virtual void loseHP(int loss);
    bool hasHoard() const;
};

#endif /* defined(__cc3k__dragon__) */
