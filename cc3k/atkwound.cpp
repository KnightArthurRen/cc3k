//
//  atkwound.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "atkwound.h"

AtkWound::AtkWound(PC *pc, int amount): StatusEffect(pc, amount) {}


AtkWound::~AtkWound() {}


int AtkWound::getAtk() {
    int temp = pc->getAtk() - amount;
    return temp >= 0 ? temp : 0;
} // getAtk
