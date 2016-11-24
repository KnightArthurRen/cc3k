//
//  troll.h
//  void
//
//  Created by Arthur Ren on 2015-07-17.
//  Copyright (c) 2015 Arthur Ren. All rights reserved.
//

#ifndef __void__troll__
#define __void__troll__

#include "pc.h"

class Troll: public PC {
    static const int Troll_MaxHP;
    static const int Troll_Atk;
    static const int Troll_Def;
    static const int recoverHP;
public:
    Troll();
    Troll(const Troll &source);
    virtual void race_special();
};

#endif /* defined(__void__troll__) */
