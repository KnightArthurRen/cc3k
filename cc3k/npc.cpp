//
//  npc.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "npc.h"
#include <cstdlib>

void NPC::generateGold() {
    // 50% small and 50% normal
    const int odd = rand() % 2;
    if (odd == 0) {
        gold_carried = new Gold(Gold::SMALL);
    } else {
        gold_carried = new Gold(Gold::NORMAL);
    } // if, else
} // generateGold


NPC::NPC() {}


NPC::~NPC() {}


int NPC::attack(Character &defender) {
    // 50% chance to miss
    const int odd = rand() % 2;
    if (odd == 0) {
        return -1;
    } // if
    return Character::attack(defender);
} // attack


Gold *NPC::gold_hold() {
    return gold_carried;
} // gold_hold


bool NPC::isHostile() const {
    return true;
} // isHostile