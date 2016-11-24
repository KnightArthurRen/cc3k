//
//  npc.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__npc__
#define __cc3k__npc__

#include "character.h"
#include "gold.h"

class NPC:public Character {
protected:
    // generate a gold and store it in gold_carried
    // 50% chance the gold will be small and 50% chance for normal
    void generateGold();

public:
    NPC();      // default ctor
    virtual ~NPC() = 0;     // default dtor
    
    virtual int attack(Character &defender);
    
    virtual Gold *gold_hold();
    
    virtual bool isHostile() const;
};

#endif /* defined(__cc3k__npc__) */
