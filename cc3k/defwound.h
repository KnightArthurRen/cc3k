//
//  defwound.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__defwound__
#define __cc3k__defwound__

#include "status_effect.h"
class DefWound: public StatusEffect {
public:
    DefWound(PC *pc, int amount);
    ~DefWound();
    virtual int getDef();
};
#endif /* defined(__cc3k__defwound__) */
