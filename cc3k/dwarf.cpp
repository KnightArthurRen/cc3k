//
//  dwarf.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "dwarf.h"

const int Dwarf::Dwarf_MaxHP = 100;
const int Dwarf::Dwarf_Atk = 20;
const int Dwarf::Dwarf_Def = 30;

Dwarf::Dwarf() {
    race = DWARF;
    MaxHP = Dwarf_MaxHP;
    HP = MaxHP;
    Atk = Dwarf_Atk;
    Def = Dwarf_Def;
    generateGold();
} // default ctor
