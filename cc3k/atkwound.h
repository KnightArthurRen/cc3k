//
//  atkwound.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__atkwound__
#define __cc3k__atkwound__

#include "status_effect.h"

class AtkWound: public StatusEffect {
public:
    AtkWound(PC *pc, int amount);
    ~AtkWound();
    virtual int getAtk();
};
#endif /* defined(__cc3k__atkwound__) */
