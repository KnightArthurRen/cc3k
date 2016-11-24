//
//  merchant.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "merchant.h"

const int Merchant::Merchant_MaxHP = 30;
const int Merchant::Merchant_Atk = 70;
const int Merchant::Merchant_Def = 5;
bool Merchant::hostility = false;

void Merchant::resetHostility() {
    hostility = false;
} // resetHostility


Merchant::Merchant() {
    race = MERCHANT;
    MaxHP = Merchant_MaxHP;
    HP = MaxHP;
    Atk = Merchant_Atk;
    Def = Merchant_Def;
    gold_carried = new Gold(Gold::MERCHANT);
} // default ctor


void Merchant::loseHP(int loss) {
    hostility = true;
    Character::loseHP(loss);
} // loseHP


bool Merchant::isHostile() const {
    return hostility;
} // isHostile
