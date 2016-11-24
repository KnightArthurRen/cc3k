//
//  defboost.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__defboost__
#define __cc3k__defboost__

#include "status_effect.h"

class DefBoost: public StatusEffect {
public:
    DefBoost(PC *pc, int amount);
    ~DefBoost();
    virtual int getDef();
};

#endif /* defined(__cc3k__defboost__) */
