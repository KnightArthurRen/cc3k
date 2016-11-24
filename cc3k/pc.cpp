//
//  pc.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include <cstdlib>
#include "pc.h"
#include "potion.h"

PC::PC() {}

PC::PC(const PC &source): Character(source) {}// copy ctor

PC::~PC() {}

void PC::addGold(NPC *enemy) {
    gold_carried->increase_value(enemy->gold_hold());
}

void PC::addGold(Gold *gold) {
    gold_carried->increase_value(gold);
}

int PC::getScore() {
    return getgold();
}

int PC::attack(Character &defender) {
    const int missed = rand() % 2;
    if (defender.getrace() == Character::HALFLING && missed) {   //%50 of missing if defender is Halfing
        return -1;
    } else {
        return Character::attack(defender);
    } // if, else
    
}

PC *PC::consume_potion(Potion &potion) {
    return potion.produceSubject(this);
}

void PC::race_special() {}