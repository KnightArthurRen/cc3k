//
//  generate.cpp
//  generation
//
//  Created by Arthur Ren on 2015-07-22.
//  Copyright (c) 2015 Arthur Ren. All rights reserved.
//

#include "generate.h"
#include <cstdlib>

using namespace std;

//dimension of the floor
const int col = 79;
const int row = 25;

const int num_of_floors = 5;
const int num_of_chambers = 5;

//generate the first chamber
vector<Posn>* generate_chamber1() {
    vector<Posn> *chamber1 = new vector<Posn>;
    for(int row = 3; row <= 6; ++row) {     //loop through each row
        for(int col = 3; col <= 28; ++col) { //loop through each col
            chamber1->push_back(Posn(col, row));
        } //for
    } //for
    return chamber1;
}

//generate the second chamber
vector<Posn>* generate_chamber2() {
    vector<Posn> *chamber2 = new vector<Posn>;
    for(int row = 15; row <= 21; ++row) {   //loop through each row
        for(int col = 4; col <= 24; ++col) {    //loop through each col
            chamber2->push_back(Posn(col, row));
        } //for
    } //for
    return chamber2;
}

//generate the third chamber
vector<Posn>* generate_chamber3() {
    vector<Posn> *chamber3 = new vector<Posn>;
    for(int row = 10; row <= 12; ++row) { //loop through each row
        for(int col = 38; col <= 49; ++col) {   //loop through each col
            chamber3->push_back(Posn(col, row));
        } //for
    } //for
    return chamber3;
}

//generate the forth chamber
vector<Posn>* generate_chamber4() {
    vector<Posn> *chamber4 = new vector<Posn>;
    for(int row = 3; row <= 6; ++row) { //loop through each row of the first rectangle part of the chamber
        for(int col = 39; col <= 61; ++col) {   //loop through each col of the first rectangle part of the chamber
            chamber4->push_back(Posn(col,row));
        } //for
    } //for
    for(int row = 5; row <= 6; ++row) { //loop through each row of the second rectangle part of the chamber
        for(int col = 62; col <= 69; ++col) { //loop through each col of the second retangle part of the chamber
            chamber4->push_back(Posn(col, row));
        } //for
    } //for
    chamber4->push_back(Posn(70, 6));
    chamber4->push_back(Posn(71, 6));
    chamber4->push_back(Posn(72, 6));     //individually generaete three positions that is not in any of the rectangles
    for(int row = 7; row <= 12; ++row) {    //loop through each row of the third rectangle part of the chamber
        for(int col = 61; col <= 75; ++col) {   //loop through each col of the third rectangl part of the chamber
            chamber4->push_back(Posn(col, row));
        } //for
    } //for
    return chamber4;
}

//generate the fifth chamber
vector<Posn>* generate_chamber5() {
    vector<Posn> *chamber5 = new vector<Posn>;
    for(int row = 16; row <= 18; ++row) {   //loop through each row of the first rectangle part of the chamber
        for(int col = 65; col <= 75; ++col) {   //loop through each col of the first rectangle part of the chamber
            chamber5->push_back(Posn(col, row));
        } //for
    } //for
    for(int row = 19; row <= 21; ++row) {   //loop through each row of the second rectangle part of the chamber
        for(int col = 37; col <= 75; ++col) {   //loop through each col of the second rectangle part of the chamber
            chamber5->push_back(Posn(col, row));
        } //for
    } //for
    return chamber5;
}

//convert a class Posn to it's correspond position in a string
int posn_index_convert(Posn &position) {
    return position.getrow() * col + position.getcol();
}

// generate the pc into a floor
int generate_pc(vector<Posn> *chambers[], int num_of_chambers, string *floor) {
    int chamber_of_pc = rand() % num_of_chambers;  //which chamber the pc is generated
    int rand_range = static_cast<int>(chambers[chamber_of_pc]->size());
    int position_of_pc = rand() % rand_range;
    Posn &location = chambers[chamber_of_pc]->at(position_of_pc);  //the position of pc
    if(posn_index_convert(location) < static_cast<int>(floor->size())) {  //ensure not out-of-range
        floor->at(posn_index_convert(location)) = '@';
        location.isoccupied = true;                             //denote the position as being occupied
    } //if
    return chamber_of_pc;
}

//generate the stair into a floor
void generate_stair(vector<Posn> *chambers[], int num_of_chambers, int chamber_of_pc, string *floor) {
    int chamber_of_stair = rand() % num_of_chambers;  //which chamber the stair is generated
    while(chamber_of_stair == chamber_of_pc) {  // ensure pc and stair is not in the same chamber
        chamber_of_stair = rand() % num_of_chambers;
    } //while
    int rand_range = static_cast<int>(chambers[chamber_of_stair]->size());
    int position_of_stair = rand() % rand_range;
    Posn &location = chambers[chamber_of_stair]->at(position_of_stair); //the position of stair
    if(posn_index_convert(location) < static_cast<int>(floor->size())) {      //ensure not out-of-range
        floor->at(posn_index_convert(location)) = '\\';
        location.isoccupied = true;                             //denote the position as being occupied
    } //if
}

const int num_of_potion_types = 6;
const int num_of_potion_per_floor = 10;

//generate the potions into a floor
void generate_potion(vector<Posn> *chambers[], int num_of_chambers, string *floor) {
    for(int i = 0; i < num_of_potion_per_floor; ++i) {       // generate 10 potions in one floor
        int chamber_of_potion = rand() % num_of_chambers;
        int rand_range = static_cast<int>(chambers[chamber_of_potion]->size());
        int position_of_potion = rand() % rand_range;
        Posn *location = &(chambers[chamber_of_potion]->at(position_of_potion)); //the position of the potion
        while(floor->at(posn_index_convert(*location)) != '.') {         // if the destination position is occupied
            position_of_potion = rand() % rand_range;                       // re-position the potion
            location = &(chambers[chamber_of_potion]->at(position_of_potion));
        }
        int type_of_potion = rand() % num_of_potion_types;
        if(posn_index_convert(*location) < static_cast<int>(floor->size())) {      //ensure not out-of-range
            floor->at(posn_index_convert(*location)) = '0' + type_of_potion;
            location->isoccupied = true;                             //denote the position as being occupied
        } //if
    } //for
}

//check if the position is a vaild and unoccupied position
bool vaild_posn(Posn &position, string *floor) {
    if(position.getrow() >= 0 && position.getrow() <= row -1 &&
       position.getrow() >= 0 && position.getcol() <= col -1) {     //if vaild row and colindex
        // if not out-of-range and is not occupied
        if(posn_index_convert(position) < static_cast<int>(floor->size()) && floor->at(posn_index_convert(position)) == '.') {
            return true;
        } else {
            return false;
        } //if
    } else {
        return false;
    } //if
}

// check if the position on the current floor is able to fit a dragon hoard
bool possible_dragon_hoard(Posn &position, string *floor) {
    Posn NO(position.getcol(), position.getrow() -1);     // NO Posn of the current Posn
    Posn SO(position.getcol(), position.getrow() +1);     // SO Posn of the current Posn
    Posn EA(position.getcol() +1, position.getrow());     // EA Posn of the current Posn
    Posn WE(position.getcol() -1, position.getrow());     // WE Posn of the current Posn
    Posn NE(position.getcol() +1, position.getrow() -1);  // NE Posn of the current Posn
    Posn NW(position.getcol() -1, position.getrow() -1);  // NW Posn of the current Posn
    Posn SE(position.getcol() +1, position.getrow() +1);  // SE Posn of the current Posn
    Posn SW(position.getcol() -1, position.getrow() +1);  // SW Posn of the current Posn
    if(floor->at(posn_index_convert(position)) != '.') {               //if the position is occupied
        return false;
    } else if(vaild_posn(NO, floor)) { //if NO position is not occupied
        return true;
    } else if(vaild_posn(SO, floor)) { //if SO position is not occupied
        return true;
    } else if(vaild_posn(EA, floor)) { //if EA position is not occupied
        return true;
    } else if(vaild_posn(WE, floor)) { //if WE position is not occupied
        return true;
    } else if(vaild_posn(NE, floor)) { //if NE position is not occupied
        return true;
    } else if(vaild_posn(NW, floor)) { //if NW position is not occupied
        return true;
    } else if(vaild_posn(SE, floor)) { //if SE position is not occupied
        return true;
    } else if(vaild_posn(SW, floor)) { //if SW position is not occupied
        return true;
    } else {
        return false;                       //if all adjacent position are occupied
    }//if
}

//generate the dragon into the floor with the given position of it's dragon hoard
void generate_dragon(Posn &position, string *floor) {
    char dragon = 'D';
    const int directions = 8;     //total number of possible adjacent position
    int position_of_dragon = rand() % directions;
    Posn location;
    if(position_of_dragon == no) {
        location = Posn(position.getcol(), position.getrow() -1);     // NO Posn of the current Posn
    } else if(position_of_dragon == so) {
        location = Posn(position.getcol(), position.getrow() +1);     // SO Posn of the current Posn
    } else if(position_of_dragon == ea) {
        location = Posn(position.getcol() +1, position.getrow());     // EA Posn of the current Posn
    } else if(position_of_dragon == we) {
        location = Posn(position.getcol() -1, position.getrow());     // WE Posn of the current Posn
    } else if(position_of_dragon == ne) {
        location = Posn(position.getcol() +1, position.getrow() -1);  // NE Posn of the current Posn
    } else if(position_of_dragon == nw) {
        location = Posn(position.getcol() -1, position.getrow() -1);  // NW Posn of the current Posn
    } else if(position_of_dragon == se) {
        location = Posn(position.getcol() +1, position.getrow() +1);  // SE Posn of the current Posn
    } else {
        location = Posn(position.getcol() -1, position.getrow() +1);  // SW Posn of the current Posn
    } //if
    while(floor->at(posn_index_convert(location)) != '.') {     // if the location is occupied, re-position dragon
        int position_of_dragon = rand() % directions;
        if(position_of_dragon == no) {
            location = Posn(position.getcol(), position.getrow() -1);     // NO Posn of the current Posn
        } else if(position_of_dragon == so) {
            location = Posn(position.getcol(), position.getrow() +1);     // SO Posn of the current Posn
        } else if(position_of_dragon == ea) {
            location = Posn(position.getcol() +1, position.getrow());     // EA Posn of the current Posn
        } else if(position_of_dragon == we) {
            location = Posn(position.getcol() -1, position.getrow());     // WE Posn of the current Posn
        } else if(position_of_dragon == ne) {
            location = Posn(position.getcol() +1, position.getrow() -1);  // NE Posn of the current Posn
        } else if(position_of_dragon == nw) {
            location = Posn(position.getcol() -1, position.getrow() -1);  // NW Posn of the current Posn
        } else if(position_of_dragon == se) {
            location = Posn(position.getcol() +1, position.getrow() +1);  // SE Posn of the current Posn
        } else {
            location = Posn(position.getcol() -1, position.getrow() +1);  // SW Posn of the current Posn
        } //if
    } //while
    if(posn_index_convert(location) < static_cast<int>(floor->size())) {      //ensure not out-of-range
        floor->at(posn_index_convert(location)) = dragon;
        location.isoccupied = true;
    } //if
}

const int gold_generate_constant = 8;
const int normal_gold_odd = 4;
const int dragon_hoard_odd = 7;
const int num_of_gold_per_floor = 10;

//generate gold piles into the floor
void generate_gold(vector<Posn> *chambers[], int num_of_chambers, string *floor) {
    for(int i = 0; i < num_of_gold_per_floor; ++i) {                            // generate 10 golds per floor
        int chamber_of_gold = rand() % num_of_chambers;
        int type_of_gold = rand() % gold_generate_constant;
        if(type_of_gold != dragon_hoard_odd) {                                  // if generating regular gold pile
            int rand_range = static_cast<int>(chambers[chamber_of_gold]->size());
            int position_of_gold = rand() % rand_range;
            Posn &location = chambers[chamber_of_gold]->at(position_of_gold);    // the position of the gold
            while(floor->at(posn_index_convert(location)) != '.') {         // if the destination position is
                position_of_gold = rand() % rand_range;                        // occupied
                location = chambers[chamber_of_gold]->at(position_of_gold);     // re-position the gold
            } //while
            if(posn_index_convert(location) < static_cast<int>(floor->size())) {      //ensure not out-of-range
                if(type_of_gold <= normal_gold_odd) {                                // if generating normal pile
                    floor->at(posn_index_convert(location)) = '6';
                } else {
                    floor->at(posn_index_convert(location)) = '7';
                } //if
                location.isoccupied = true;                             //denote the position as being occupied
            }
        } else {
            vector<Posn> dragon_hoard_choices;
            for(vector<Posn>::iterator it = chambers[chamber_of_gold]->begin();     // filter positions that can't put
                it != chambers[chamber_of_gold]->end(); ++it) {                     // in a dragon hoard
                if(possible_dragon_hoard(*it, floor)) {
                    dragon_hoard_choices.push_back(*it);
                }
            }
            while(dragon_hoard_choices.size() == 0) {   //if the chamber can't fit a dragon hoard, switch to an new one
                chamber_of_gold = rand() % num_of_chambers;
                for(vector<Posn>::iterator it = chambers[chamber_of_gold]->begin();     // filter positions that can't
                    it != chambers[chamber_of_gold]->end(); ++it) {                     // put in a dragon hoard
                    if(possible_dragon_hoard(*it, floor)) {
                        dragon_hoard_choices.push_back(*it);
                    }
                }
            }
            int rand_range = static_cast<int>(dragon_hoard_choices.size());
            int position_of_gold = rand() % rand_range;
            Posn &location = dragon_hoard_choices.at(position_of_gold);    // the position of the dragon hoard
            if(posn_index_convert(location) < static_cast<int>(floor->size())) {      //ensure not out-of-range
                floor->at(posn_index_convert(location)) = '9';
                location.isoccupied = true;                             //denote the position as being occupied
                generate_dragon(location, floor);
            } //if
        } //if
    } //for
}

//check if the given chamber is full
bool full_chamber(vector<Posn> *chamber, string *floor){
    for(vector<Posn>::iterator it = chamber->begin(); it != chamber->end(); ++it) { //loop through the chamber
        if(floor->at(posn_index_convert(*it)) != '.') {                                                     //if the position is not occupied
            return true;
        } //if
    }// for
    return false;                                                                 //if all position is occupied
}

const int num_of_enemy_per_floor = 20;
const int enemy_generate_const = 18;
const int odd_of_human = 3;
const int odd_of_drwaf = 6;
const int odd_of_halfing = 11;
const int odd_of_elf = 13;
const int odd_of_orc = 15;

//generate enemys into the floor
void generate_enemy(vector<Posn> *chambers[], int num_of_chambers, string *floor) {
    char human = 'H';
    char dwarf = 'W';
    char elf = 'E';
    char orc = 'O';
    char merchant = 'M';
    char halfing = 'L';
    for(int i = 0; i < num_of_enemy_per_floor; ++i) {              //generate 20 enemy per floor
        int chamber_of_enemy = rand() % num_of_chambers;
        while(!full_chamber(chambers[chamber_of_enemy], floor)) {         //if the chamber is full, seek another chamber
            chamber_of_enemy = rand() % num_of_chambers;
        } //while
        int rand_range = static_cast<int>(chambers[chamber_of_enemy]->size());
        int position_of_enemy = rand() % rand_range;
        Posn &location = chambers[chamber_of_enemy]->at(position_of_enemy);
        while(floor->at(posn_index_convert(location)) != '.') {                               //if the location is occupied, find a new one
            position_of_enemy = rand() % rand_range;
            location = chambers[chamber_of_enemy]->at(position_of_enemy);
        } //while
        int type_of_enemy = rand() % enemy_generate_const;
        if(posn_index_convert(location) < static_cast<int>(floor->size())) {         //ensure not out-of-range
            if(type_of_enemy <= odd_of_human) {                    //if a human is generated
                floor->at(posn_index_convert(location)) = human;
            } else if(type_of_enemy <= odd_of_drwaf) {             //if a dwarf is generated
                floor->at(posn_index_convert(location)) = dwarf;
            } else if(type_of_enemy <= odd_of_halfing) {          //if a halfing is generated
                floor->at(posn_index_convert(location)) = halfing;
            } else if(type_of_enemy <= odd_of_elf) {             //if a elf is generated
                floor->at(posn_index_convert(location)) = elf;
            } else if(type_of_enemy <= odd_of_orc) {             //if a orc is generated
                floor->at(posn_index_convert(location)) = orc;
            } else {                                             //if a mearchant is generated
                floor->at(posn_index_convert(location)) = merchant;
            } //if
        } //if
    } //for
}

void generate_floor(string inputfile, string outputfile) {
    srand(static_cast<unsigned>(time(0)));
    ofstream generated_floor(outputfile.c_str());
    vector<Posn> *chamber1 = generate_chamber1();
    vector<Posn> *chamber2 = generate_chamber2();
    vector<Posn> *chamber3 = generate_chamber3();
    vector<Posn> *chamber4 = generate_chamber4();
    vector<Posn> *chamber5 = generate_chamber5();
    for(int i = 0; i < num_of_floors; ++i) { //construct all required number of floors
        ifstream layout(inputfile.c_str());
        string lines;
        string floor;
        while(getline(layout, lines)) { //read the empty floor input
        floor.append(lines);
        } //while
                        //generate all 5 chambers
        vector<Posn> *allchamber[num_of_chambers] = {chamber1,chamber2,chamber3,chamber4,chamber5};
        int pc_chamber = generate_pc(allchamber, num_of_chambers, &floor);
        generate_stair(allchamber, num_of_chambers, pc_chamber, &floor);
        generate_potion(allchamber, num_of_chambers, &floor);
        generate_gold(allchamber, num_of_chambers, &floor);
        generate_enemy(allchamber, num_of_chambers, &floor);
        while(floor != "") {                        //output the generated floor to the outputfile
            string one_line = floor.substr(0,col);
            generated_floor << one_line;
            generated_floor << "\n";
            floor = floor.substr(col);
        }
    } //for
    delete chamber1;
    delete chamber2;
    delete chamber3;
    delete chamber4;
    delete chamber5;
    generated_floor.close();
}
