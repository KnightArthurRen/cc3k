//
//  human.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "human.h"
#include "gold.h"

const int Human::Human_MaxHP = 140;
const int Human::Human_Atk = 20;
const int Human::Human_Def = 20;
const int Human::Human_Gold = 2 * Gold::NORMAL;

Human::Human() {
    race = HUMAN;
    MaxHP = Human_MaxHP;
    HP = MaxHP;
    Atk = Human_Atk;
    Def = Human_Def;
    gold_carried = new Gold(Human_Gold);
} // default ctor
