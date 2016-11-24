//
//  atkboost.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "atkboost.h"


AtkBoost::AtkBoost(PC *pc, int amount): StatusEffect(pc, amount) {}

AtkBoost::~AtkBoost() {}

int AtkBoost::getAtk() { return pc->getAtk() + amount; }
