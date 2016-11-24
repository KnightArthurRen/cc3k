//
//  potion.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include <cmath>
#include "potion.h"
#include "pc.h"
#include "drow.h"
#include <iostream>

using namespace std;

bool Potion::visibility[Potion::numPotionTypes] = {false};

const int Atk_potion_effect = 5;    // effect for Atk Boost/Wound Potion
const int Def_potion_effect = 5;    // effect for Def Boost/Wound Potion
const int HP_potion_effect = 10;    // effect for HP Restore/Poison Potion

// race special for Drow when taking the Posion
const float Drow_potion_effect = 1.5;


void Potion::resetVisibility() {
#ifdef DEBUG
    cout<<"resetting potions' visibility"<<endl;
#endif
    for (unsigned int i = 0; i < numPotionTypes; ++i) {
#ifdef DEBUG
        cout<<"resetting number"<<i<<endl;
#endif        
        visibility[i] = false;
    } // for
} // resetVisibility


string Potion::effectToStr(Potion::Effect effect) {
    if (effect == RH) {
        return "RH";
    } // if
    if (effect == BA) {
        return "BA";
    } // if
    if (effect == BD) {
        return "BD";
    } // if
    if (effect == PH) {
        return "PH";
    } // if
    if (effect == WA) {
        return "WA";
    } // if
    return "WD";
    
} // effectToStr


// default Potion constructor
Potion::Potion(char effect): effect(static_cast<Effect>(effect)) {}

Potion::~Potion() {}

Potion::Effect Potion::getEffect() const {
    return effect;
} // getEffect

// Potion effect for all non-Drow race
PC *Potion::produceSubject(PC *pc) {
    if (pc->getrace() == Character::DROW) {
        return produceDrow(pc);
    } // if

    visibility[effect - '0'] = true;
    if(getEffect() == RH) {                                            //RH Posion
        pc->gainHP(HP_potion_effect);
        return pc;
    } else if(getEffect() == BA) {
        PC *pc_with_boost_atk = new AtkBoost(pc, Atk_potion_effect);    //BA Potion
        return pc_with_boost_atk;
    } else if(getEffect() == BD) {
        PC *pc_with_boost_def = new DefBoost(pc, Def_potion_effect);    //BD Potion
        return pc_with_boost_def;
    } else if(getEffect() == PH) {
        pc->loseHP(HP_potion_effect);                                   //PH Potion
        return pc;
    } else if(getEffect() == WA) {
        PC *pc_with_wound_atk = new AtkWound(pc, Atk_potion_effect);    //WA Potion
        return pc_with_wound_atk;
    } else {
        PC *pc_with_wound_def = new DefWound(pc, Def_potion_effect);    //WD Potion
        return pc_with_wound_def;
    }
} // produceSubject(PC)

// Potion effect for Drow race
PC *Potion::produceDrow(PC *pc) {
    visibility[effect - '0'] = true;
    if(getEffect() == RH) {
        pc->gainHP(ceil(HP_potion_effect * Drow_potion_effect));                                   //RH Potion
        return pc;
    } else if(getEffect() == BA) {
        PC *pc_with_boost_atk = new AtkBoost(pc, ceil(Atk_potion_effect * Drow_potion_effect));    //BA Potion
        return pc_with_boost_atk;
    } else if(getEffect() == BD) {
        PC *pc_with_boost_def = new DefBoost(pc, ceil(Def_potion_effect * Drow_potion_effect));    //BD Potion
        return pc_with_boost_def;
    } else if(getEffect() == PH) {
        pc->loseHP(ceil(HP_potion_effect * Drow_potion_effect));                                   //PH Potion
        return pc;
    } else if(getEffect() == WA) {
        PC *pc_with_wound_atk = new AtkWound(pc, ceil(Atk_potion_effect * Drow_potion_effect));    //WA Potion
        return pc_with_wound_atk;
    } else {
        PC *pc_with_wound_def = new DefWound(pc, ceil(Def_potion_effect * Drow_potion_effect));    //WD Potion
        return pc_with_wound_def;
    }
} // produceDrow(PC)


bool Potion::isVisible() const {
    return visibility[effect - '0'];
} // isVisible

