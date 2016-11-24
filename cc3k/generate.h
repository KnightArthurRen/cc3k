//
//  generate.h
//  generation
//
//  Created by Arthur Ren on 2015-07-22.
//  Copyright (c) 2015 Arthur Ren. All rights reserved.
//

#ifndef __generation__generate__
#define __generation__generate__

#include "posn.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

//all possible adjacent positions for each position
enum directions { no = 0, so = 1, ea = 2, we = 3, ne = 4, nw = 5, se = 6, sw = 7};

//generate_floor consumes two strings, the first is the input file which the function read in the empty floor
//    from, the second one is where the function will put the generated floors in.
void generate_floor(std::string inputfile, std::string outputfile);

#endif /* defined(__generation__generate__) */
