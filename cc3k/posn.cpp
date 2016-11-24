//
//  posn.cpp
//  generation
//
//  Created by Arthur Ren on 2015-07-22.
//  Copyright (c) 2015 Arthur Ren. All rights reserved.
//

#include "posn.h"

int Posn::getrow() const{
    return row;
} // getrow


int Posn::getcol() const{
    return col;
} // getrow


Posn::Posn() {}


Posn::Posn(int col, int row): col(col), row(row), isoccupied(false) {}
