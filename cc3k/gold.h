//
//  gold.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__gold__
#define __cc3k__gold__

#include "character.h"

class Gold {
    int value;
public:
    enum Pile {SMALL = 1, NORMAL = 2, MERCHANT = 4, DRAGON = 6};
    
    Gold(int value);   // ctor with value passed in
    ~Gold();
    int getValue();
    void increase_value(Gold *amount);
    virtual bool pickable() const;
};

#endif

