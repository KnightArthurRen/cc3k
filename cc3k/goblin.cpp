//
//  goblin.cpp
//  void
//
//  Created by Arthur Ren on 2015-07-17.
//  Copyright (c) 2015 Arthur Ren. All rights reserved.
//

#include "goblin.h"
#include "gold.h"

// the following is the default race of Goblin

const int Goblin::Goblin_maxHP = 110;
const int Goblin::Goblin_Atk = 15;
const int Goblin::Goblin_Def = 20;

// Goblin gold bonus modifier
const int Goblin::Goblin_gold_bonus = 5;


Goblin::Goblin(): PC() {
    race = Character::GOBLIN;
    gold_carried = new Gold(0);
    HP = Goblin_maxHP;
    Atk = Goblin_Atk;
    Def = Goblin_Def;
    MaxHP = Goblin_maxHP;
} // default ctor


Goblin::Goblin(const Goblin &source): PC(source) {};


void Goblin::addGold(NPC *enemy) {
    PC::addGold(enemy);
    Gold *bonus = new Gold(Goblin_gold_bonus);
    gold_carried->increase_value(bonus);
    delete bonus;
}
