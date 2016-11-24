//
//  character.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include <cmath>
#include <cstdlib>
#include "character.h"
#include "gold.h"

const int def_modifier = 100;
//the less it gets, the more damage the defender can take, global for all PC/NPC

Character::Character() {gold_carried = NULL;}


Character::Character(const Character &source) {
    race = source.race;
    HP = source.HP;
    Atk = source.Atk;
    Def = source.Def;
    MaxHP = source.MaxHP;
    gold_carried = new Gold(*(source.gold_carried));
} // copy ctor


Character::~Character() {
    delete gold_carried;
}


Character::RACE Character::getrace() {
    return race;
}

int Character::getHP() {
    return HP;
}
int Character::getAtk() {
    return Atk;
}

int Character::getDef() {
    return Def;
}

int Character::getgold() {
    return gold_carried->getValue();
}


int  Character::getMaxHP() {
    return MaxHP;
}


void Character::loseHP(int loss) {
    HP = HP - loss > 0 ? HP - loss : 0;
}


void Character::gainHP(int gain) {
    HP += gain;
    if(MaxHP == -1) {       // if character is Vampire, no HP celing
    } else if(MaxHP < HP) { // if the character(not _Vampire)'s HP after gain has exceeded the MaxHP,
        // reset HP to the maxHP
        HP = getMaxHP();
    } else {                // if the character's HP have not yet reached maximum, normally add the HP;
    }
}


// standard attack calculation
int Character::attack(Character &defender) {
    int damage = ceil((static_cast<float>(def_modifier) / (def_modifier + defender.getDef())) * this->getAtk());
    damage = damage < 0 ? 0 : damage;
    defender.loseHP(damage);
    return damage;
}

