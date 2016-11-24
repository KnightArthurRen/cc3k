//
//  defboost.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "defboost.h"

DefBoost::DefBoost(PC *pc, int amount): StatusEffect(pc, amount) {}

DefBoost::~DefBoost() {}

int DefBoost::getDef() { return pc->getDef() + amount; }