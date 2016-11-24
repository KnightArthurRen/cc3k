//
//  defwound.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "defwound.h"

DefWound::DefWound(PC *pc, int amount): StatusEffect(pc, amount) {}

DefWound::~DefWound() {}

int DefWound::getDef() {
    int temp = pc->getDef() - amount;
    return temp >= 0 ? temp : 0;
}
