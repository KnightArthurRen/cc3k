//
//  posn.h
//  generation
//
//  Created by Arthur Ren on 2015-07-22.
//  Copyright (c) 2015 Arthur Ren. All rights reserved.
//

#ifndef __generation__posn__
#define __generation__posn__

class Posn {
    int col;
    int row;
public:
    bool isoccupied;
    int getcol() const;
    int getrow() const;
    Posn();
    Posn(int col, int row);
};

#endif /* defined(__generation__posn__) */
