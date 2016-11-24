//
//  orcs.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "orcs.h"
#include <cmath>
#include <cstdlib>

const int Orcs::Orcs_MaxHP = 180;
const int Orcs::Orcs_Atk = 30;
const int Orcs::Orcs_Def = 25;

Orcs::Orcs() {
    race = ORCS;
    MaxHP = Orcs_MaxHP;
    HP = MaxHP;
    Atk = Orcs_Atk;
    Def = Orcs_Def;
    generateGold();
} // default ctor


int Orcs::attack(Character &defender) {
    // 50% chance to miss
    const int odd = rand() % 2;
    if (odd == 0) {
        return -1;
    } // if
    
    const int def_modifier = 100;
    const float dmgMultGoblin = 1.5;
    int damage = ceil((static_cast<float>(def_modifier) / (def_modifier + defender.getDef())) * this->getAtk());
    damage = damage < 0 ? 0 : damage;
    // damage bonus to GOBLIN
    if (defender.getrace() == GOBLIN) {
        damage = ceil(damage * dmgMultGoblin);
    } // if
    defender.loseHP(damage);
    return damage;
} // attack
