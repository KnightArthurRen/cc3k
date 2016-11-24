//
//  pc.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__pc__
#define __cc3k__pc__

#include "character.h"
#include "npc.h"
#include "gold.h"

class Potion;

class PC: public Character {
public:
    PC();
    PC(const PC &source);
    virtual ~PC() = 0;
    // get gold from a dead enemy
    virtual void addGold(NPC *enemy);
    // get gold from a gold pile
    virtual void addGold(Gold *gold);
    virtual int attack(Character &defender);
    virtual int getScore();
    PC *consume_potion(Potion &potion);
    virtual void race_special();
};


#endif /* defined(__cc3k__pc__) */
