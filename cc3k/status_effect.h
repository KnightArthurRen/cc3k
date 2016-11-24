//
//  status_effect.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__status_effect__
#define __cc3k__status_effect__

#include "pc.h"

// effect of the Atk/Def Boost/Wound Potion

class StatusEffect: public PC {
protected:
    PC *pc;         //player
    int amount;     //effect amount
public:
    StatusEffect(PC *pc, int amount);
    virtual ~StatusEffect() = 0;
    
    // StatusEffect version of PC public methods
    // get gold from a dead enemy
    virtual void addGold(NPC *enemy);
    // get gold from a gold pile
    virtual void addGold(Gold *gold);
    virtual int attack(Character &defender);
    virtual int getScore();
    PC *consume_potion(Potion &potion);
    virtual void race_special();
    
    // StatusEffect version of Character public methods
    virtual RACE getrace();
    virtual int getHP();
    virtual int getAtk();
    virtual int getDef();
    virtual int getgold();
    virtual int getMaxHP();
    virtual void loseHP(int loss);
    virtual void gainHP(int gain);
    
};

#endif /* defined(__cc3k__status_effect__) */
