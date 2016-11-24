//
//  halfling.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__halfling__
#define __cc3k__halfling__

#include "npc.h"

class Halfling: public NPC {
    static const int Halfling_MaxHP;
    static const int Halfling_Atk;
    static const int Halfling_Def;
public:
    Halfling();    // default ctor
    
};

#endif /* defined(__cc3k__halfling__) */
