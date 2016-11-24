//
//  gold.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include "gold.h"

Gold::Gold(int value): value(value) {}


Gold::~Gold() {}


int Gold::getValue() {
    return value;
} // getValue


void Gold::increase_value(Gold *amount) {
    value += amount->getValue();
} // increase_value


bool Gold::pickable() const {
    return true;
} // pickable

