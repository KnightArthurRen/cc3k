//
//  drow.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "drow.h"

// the following is the default race of Drow
const int Drow::Drow_maxHP = 150;
const int Drow::Drow_Atk = 25;
const int Drow::Drow_Def = 15;

//default Drow constructor
Drow::Drow(): PC() {
    race = Character::DROW;
    gold_carried = new Gold(0);
    HP = Drow_maxHP;
    Atk = Drow_Atk;
    Def = Drow_Def;
    MaxHP = Drow_maxHP;
}


Drow::Drow(const Drow &source): PC(source) {};