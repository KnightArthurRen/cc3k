//
//  goblin.h
//  void
//
//  Created by Arthur Ren on 2015-07-17.
//  Copyright (c) 2015 Arthur Ren. All rights reserved.
//

#ifndef __void__goblin__
#define __void__goblin__

#include "pc.h"

class NPC;

class Goblin: public PC {
    static const int Goblin_maxHP;
    static const int Goblin_Atk;
    static const int Goblin_Def;
    static const int Goblin_gold_bonus;
public:
    Goblin();
    Goblin(const Goblin &source);
    // Goblin get extra gold when slain an enemy
    virtual void addGold(NPC *enemy);
};
#endif /* defined(__void__goblin__) */
