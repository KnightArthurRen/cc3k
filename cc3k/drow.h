//
//  drow.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__drow__
#define __cc3k__drow__

#include "pc.h"

class Drow: public PC {
    static const int Drow_maxHP;
    static const int Drow_Atk;
    static const int Drow_Def;
    
public:
    Drow();
    Drow(const Drow &source);
};

#endif /* defined(__cc3k__drow__) */
