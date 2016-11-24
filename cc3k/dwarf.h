//
//  dwarf.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__dwarf__
#define __cc3k__dwarf__

#include "npc.h"

class Dwarf: public NPC {
    static const int Dwarf_MaxHP;
    static const int Dwarf_Atk;
    static const int Dwarf_Def;
public:
    Dwarf();    // default ctor
    
};

#endif /* defined(__cc3k__dwarf__) */
