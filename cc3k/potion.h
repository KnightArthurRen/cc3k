//
//  Potion.h
//  cc3k
//
//  Created by Arthur Ren on 2015-07-15.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__potion__
#define __cc3k__potion__

#include <string>
#include "status_effect.h"
#include "atkboost.h"
#include "atkwound.h"
#include "defboost.h"
#include "defwound.h"

class PC;
class Drow;

class Potion {
    static const unsigned int numPotionTypes = 6;
    static bool visibility[numPotionTypes];
    
public:
    enum Effect {RH = '0', BA = '1', BD = '2', PH = '3', WA = '4', WD = '5'};

private:
    Effect effect;   
    PC *produceDrow(PC *pc);   //potion for Drow race

public:
    static void resetVisibility();

    /*
     transform enum Effect ot a string
     e.g. Potion::RH -> "RH"
     Potion::WA -> "WA"
     */
    static std::string effectToStr(Effect effect);
    
    Potion(char effect);
    ~Potion();
    Effect getEffect() const;
    PC *produceSubject(PC *pc);     //potion for all non_Drow race
    bool isVisible() const ;         // return the visibility of this potion based on visibility array
};
#endif
