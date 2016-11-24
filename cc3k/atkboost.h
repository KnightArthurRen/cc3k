//
//  atkboost.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__atkboost__
#define __cc3k__atkboost__

#include "status_effect.h"

class AtkBoost: public StatusEffect {
public:
    AtkBoost(PC *pc, int amount);
    ~AtkBoost();
    virtual int getAtk();
};

#endif /* defined(__cc3k__atkboost__) */
