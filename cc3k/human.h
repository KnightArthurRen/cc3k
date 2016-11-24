//
//  human.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__human__
#define __cc3k__human__

#include "npc.h"

class Human: public NPC {
    static const int Human_MaxHP;
    static const int Human_Atk;
    static const int Human_Def;
    static const int Human_Gold;
public:
    Human();    // default ctor
    
};

#endif /* defined(__cc3k__human__) */
