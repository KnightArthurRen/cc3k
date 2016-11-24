//
//  dragon.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "dragon.h"
#include "dragonhoard.h"
#include <cstdlib>

const int Dragon::Dragon_MaxHP = 150;
const int Dragon::Dragon_Atk = 20;
const int Dragon::Dragon_Def = 20;

void Dragon::notifyHoard() {
    hoard->notify();
} // notifyHoard


Dragon::Dragon() {
    race = DRAGON;
    MaxHP = Dragon_MaxHP;
    HP = MaxHP;
    Atk = Dragon_Atk;
    Def = Dragon_Def;
    gold_carried = NULL;        // Dragon does not carries gold
    hoard = NULL;
} // default ctor


void Dragon::setHoard(DragonHoard *hoard) {
    if (hoard == NULL) {
        return;
    } // if
    
    this->hoard = hoard;
} // setHoard


void Dragon::loseHP(int loss) {
    Character::loseHP(loss);
    if (HP <= 0) {
        notifyHoard();
    } // if
} // lossHP


bool Dragon::hasHoard() const {
    return hoard != NULL ? true : false;
} // hasHoard