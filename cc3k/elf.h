//
//  elf.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__elf__
#define __cc3k__elf__

#include "npc.h"

class Elf: public NPC {
    static const int Elf_MaxHP;
    static const int Elf_Atk;
    static const int Elf_Def;
public:
    Elf();    // default ctor
    
};

#endif /* defined(__cc3k__elf__) */
