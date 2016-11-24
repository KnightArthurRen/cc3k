//
//  dragonhoard.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "dragonhoard.h"
#include "dragon.h"
#include <cstdlib>

DragonHoard::DragonHoard(): Gold(DRAGON) {
    DragonDead = true;
    dragon = NULL;
} // default ctor


bool DragonHoard::pickable() const {
    return DragonDead;
} // pickable


void DragonHoard::setDragon(Dragon *dragon) {
    if (dragon == NULL) {
        return;
    } // if
    
    this->dragon = dragon;
    DragonDead = false;
} // setDragon


void DragonHoard::notify() {
    DragonDead = true;
} // notify


int DragonHoard::notifyDragon(Character &intruder) const {
    return dragon->attack(intruder);
} // notifyDragon


Dragon * DragonHoard::getDragon() const {
    return dragon;
} // getDragon
