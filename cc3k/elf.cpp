//
//  elf.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "elf.h"

const int Elf::Elf_MaxHP = 140;
const int Elf::Elf_Atk = 30;
const int Elf::Elf_Def = 10;

Elf::Elf() {
    race = ELF;
    MaxHP = Elf_MaxHP;
    HP = MaxHP;
    Atk = Elf_Atk;
    Def = Elf_Def;
    generateGold();
} // default ctor