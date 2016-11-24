//
//  troll.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-17.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "troll.h"

const int Troll::Troll_MaxHP = 120;
const int Troll::Troll_Atk = 25;
const int Troll::Troll_Def = 15;
const int Troll::recoverHP = 5;

Troll::Troll(): PC() {
    race = Character::TROLL;
    gold_carried = new Gold(0);
    HP = Troll_MaxHP;
    Atk = Troll_Atk;
    Def = Troll_Def;
    MaxHP = Troll_MaxHP;
} // default ctor


Troll::Troll(const Troll &source): PC(source) {}


void Troll::race_special() {
    gainHP(recoverHP);
} // race_special