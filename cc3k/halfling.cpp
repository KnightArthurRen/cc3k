//
//  halfling.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "halfling.h"

const int Halfling::Halfling_MaxHP = 100;
const int Halfling::Halfling_Atk = 15;
const int Halfling::Halfling_Def = 20;

Halfling::Halfling() {
    race = HALFLING;
    MaxHP = Halfling_MaxHP;
    HP = MaxHP;
    Atk = Halfling_Atk;
    Def = Halfling_Def;
    generateGold();
} // Halfling