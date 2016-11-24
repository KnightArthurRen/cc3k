//
//  main.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-16.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include <iostream>
#include <string>
#include "controller.h"
#include "generate.h"

using namespace std;

int main(int argc, const char * argv[]) {
    bool restart = true;
    Controller *c;
    
    cout<<"Welcome to Chamber Crowler 3000!!!"<<endl;
    
    while (restart) {
        c = new Controller;
        // if passed in arg, use file init mode
        if (argc > 1) {
            restart = c->play(argv[1]);
        } else {
            char randomFile[] = "__randomFloor";
            generate_floor("__layout", randomFile);
            restart = c->play(randomFile);
        } // if, else
        delete c;
    } // while
    
    cout<<"Game over!"<<endl;
    
    return 0;
} // main