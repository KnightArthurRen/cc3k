//
//  shade.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__shade__
#define __cc3k__shade__

#include "pc.h"

class Shade: public PC {
    static const int Shade_maxHP;
    static const int Shade_Atk;
    static const int Shade_Def;
    static const float Shade_race_score_bonus;
    
public:
    virtual int getScore();
    Shade();
    Shade(const Shade &source);
};



#endif /* defined(__cc3k__shade__) */
