//
//  shade.cpp
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "shade.h"
#include <cmath>

// the following is the default race of Shade
const int Shade::Shade_maxHP = 125;
const int Shade::Shade_Atk = 25;
const int Shade::Shade_Def = 25;

const float Shade::Shade_race_score_bonus = 1.5;
// the bonus modifier shade get as the reward of joining the dark force.


Shade::Shade(): PC() {
    race = Character::SHADE;
    gold_carried = new Gold(0);
    HP = Shade_maxHP;
    Atk = Shade_Atk;
    Def = Shade_Def;
    MaxHP = Shade_maxHP;
} // default ctor


Shade::Shade(const Shade &source): PC(source) {};


// shade's bonus score calculation
int Shade::getScore() {
    return ceil(getgold() * Shade_race_score_bonus);
}
