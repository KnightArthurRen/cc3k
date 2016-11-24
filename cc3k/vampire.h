//
//  Vampire.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__Vampire__
#define __cc3k__Vampire__

#include "pc.h"

class Vampire: public PC {
    static const int Vampire_start_HP;
    static const int Vampire_Atk;
    static const int Vampire_Def;
    
    // Hematophagy constant, same effect on allergic
    static const int Vampire_blood;
    
public:
    virtual int attack(Character &defender);
    Vampire();
    Vampire(const Vampire &source);
};

#endif /* defined(__cc3k__Vampire__) */
