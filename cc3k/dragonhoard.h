//
//  dragonHoard.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__dragonhoard__
#define __cc3k__dragonhoard__

#include "gold.h"

class Character;
class Dragon;

class DragonHoard: public Gold {
    static const int DragonHoard_value;
    
    Dragon *dragon;
    bool DragonDead;
public:
    // construct DragonHoard with the value ot 6 gold and the condition that
    // the guarding dragon is still alive
    DragonHoard();      // default ctor
    
    virtual bool pickable() const;
    void setDragon(Dragon *dragon);
    void notify();      // should only called by dragonhoard
    int notifyDragon(Character &intruder) const;
    Dragon *getDragon() const;
};

#endif
