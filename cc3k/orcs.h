//
//  orcs.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__orcs__
#define __cc3k__orcs__

#include "npc.h"

class Character;

class Orcs: public NPC {
    static const int Orcs_MaxHP;
    static const int Orcs_Atk;
    static const int Orcs_Def;
public:
    Orcs();    // default ctor
    
    virtual int attack(Character &defender);
};

#endif /* defined(__cc3k__orcs__) */
