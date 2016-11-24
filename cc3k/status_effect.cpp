//
//  status_effect.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "status_effect.h"
#include <cstdlib>

StatusEffect::StatusEffect(PC *pc, int amount): pc(pc), amount(amount) {};


StatusEffect::~StatusEffect() {
    delete pc;
};


void StatusEffect::addGold(NPC *enemy) {
    pc->addGold(enemy);
} // addGold


void StatusEffect::addGold(Gold *gold) {
    pc->addGold(gold);
} // addGold


int StatusEffect::attack(Character &defender) {
//    return pc->attack(defender);
    
    const int damage = PC::attack(defender);
    
    // if not vampire or missed, ignore vampire's special ability
    if (getrace() != VAMPIRE || damage == -1) {
        return damage;
    } // if
    
    const int vampire_blood = 5;
    // vampire regain blood on attack, but allergic to dwarf
    if(defender.getrace() == Character::DWARF) {
        loseHP(vampire_blood);
    } else {
        gainHP(vampire_blood);
    } // if, else
    
    return damage;
    
} // attack


int StatusEffect::getScore() {
    return  pc->getScore();
} // getScore


PC * StatusEffect::consume_potion(Potion &potion) {
    return pc->consume_potion(potion);
} // consume_potion


void StatusEffect::race_special() {
    pc->race_special();
} // race_special


Character::RACE StatusEffect::getrace() {
    return pc->getrace();
} // getrace


int StatusEffect::getHP() {
    return pc->getHP();
} // getHP


int StatusEffect::getAtk() {
    return pc->getAtk();
} // getAtk


int StatusEffect::getDef() {
    return pc->getDef();
} // getDef


int StatusEffect::getgold() {
    return pc->getgold();
} // getgold


int StatusEffect::getMaxHP() {
    return pc->getMaxHP();
} // getMaxHP


void StatusEffect::loseHP(int loss) {
    pc->loseHP(loss);
} // loseHP


void StatusEffect::gainHP(int gain) {
    pc->gainHP(gain);
} // gainHP