//
//  Vampire.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "vampire.h"
// the following is the default race of Vampire

const int Vampire::Vampire_start_HP = 50;
const int Vampire::Vampire_Atk = 25;
const int Vampire::Vampire_Def = 25;

// Hematophagy constant, same effect on allergic
const int Vampire::Vampire_blood = 5;


Vampire::Vampire(): PC() {
    race = Character::VAMPIRE;
    gold_carried = new Gold(0);
    HP = Vampire_start_HP;
    Atk = Vampire_Atk;
    Def = Vampire_Def;
    MaxHP = -1;         // Vampire has no maxHP
} // default ctor


Vampire::Vampire(const Vampire &source): PC(source) {};


// Vampire would gain HP from attacked enemy, except
// when facing drawf, which will result in lossing HP
int Vampire::attack(Character &defender) {
    const int damage = PC::attack(defender);
    
    // if missed, ignore vampire's special ability
    if (damage == -1) {
        return damage;
    } // if
    
    // vampire regain blood on attack, but allergic to dwarf
    if(defender.getrace() == Character::DWARF) {
        loseHP(Vampire_blood);
    } else {
        gainHP(Vampire_blood);
    } // if, else
    
    return damage;
} // attack
