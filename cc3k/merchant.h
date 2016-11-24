//
//  merchant.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-22.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__merchant__
#define __cc3k__merchant__

#include "npc.h"

class Merchant: public NPC {
    static const int Merchant_MaxHP;
    static const int Merchant_Atk;
    static const int Merchant_Def;
    static bool hostility;
public:
    static void resetHostility();
    Merchant();    // default ctor
    virtual void loseHP(int loss);
    virtual bool isHostile() const;
};

#endif /* defined(__cc3k__merchant__) */
