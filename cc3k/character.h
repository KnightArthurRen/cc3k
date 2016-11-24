//
//  Character.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//


#ifndef cc3k_Character_h
#define cc3k_Character_h

class Gold;

class Character {
public:
    // the races of all PC and NPC in the game
    enum RACE { SHADE = 's', DROW = 'd', VAMPIRE = 'v', GOBLIN = 'g', TROLL = 't',
        HUMAN = 'H', DWARF = 'W', ELF = 'E', ORCS = 'O', MERCHANT = 'M', DRAGON = 'D', HALFLING = 'L' };
    Character();       // ctor
    virtual ~Character() = 0;   // default dtor
    virtual RACE getrace();
    virtual int getHP();
    virtual int getAtk();
    virtual int getDef();
    virtual int getgold();
    virtual int getMaxHP();
    virtual void loseHP(int loss);
    virtual void gainHP(int gain);
    virtual int attack(Character &defender);
protected:
    Character(const Character &source);
    
    Character::RACE race;
    Gold *gold_carried;
    int HP;
    int Atk;
    int Def;
    int MaxHP;
};
#endif
