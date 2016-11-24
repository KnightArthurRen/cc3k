//
//  game.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-14.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include "game.h"
#include "gold.h"
#include "dragonhoard.h"
#include "potion.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orcs.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"

using namespace std;

const int Game::rowNum = 25;
const int Game::colNum = 79;

void Game::notifyFloor() {
    notification->notifyFloor(floorNum);
} // notifyFloor


void Game::notifyRace(string race) {
    notification->notifyRace(race);
} // notifyRace


void Game::clearGame() {
    if (floor == NULL) {
        return;
    } // if
    
    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            delete floor[i * colNum + j];
        } // for
    } // for
    delete [] floor;
    floor = NULL;
    turnNum = 0;
    npcTurns.clear();
    return;
} // clearGame


Game::Game() : maxFloorNum('5') {
    floor = NULL;
    notification = NULL;
    floorChanged = false;
    turnNum = 0;
    floorNum = '1';
    pc = NULL;
    won = false;
} // default ctor


Game::~Game() {
    clearGame();
    notification = NULL;
} // default dtor


void Game::notify(int row, int col, char state) {
    // update player position
    if (state == '@') {
        playerRow = row;
        playerCol = col;
        playerPos = playerRow * colNum + playerCol;
    } // if
    if (state == '\\') {
        stairRow = row;
        stairCol = col;
        stairPos = stairRow * colNum + stairCol;
    } // if
    notification->notify(row, col, state);
} // notify


void Game::notifyGold(int gold) {
    notification->notifyGold(gold);
} // notifyGold


void Game::notifyHP(int HP) {
    notification->notifyHP(HP);
} // notifyHP


void Game::notifyAtk(int Atk) {
    notification->notifyAtk(Atk);
} // notifyAtk


void Game::notifyDef(int Def) {
    notification->notifyDef(Def);
} // notifyDef


void Game::notifyAction(string action) {
    notification->notifyAction(action);
} // notifyAction


void Game::resetPotionMerchant() {
    Potion::resetVisibility();
    Merchant::resetHostility();
} // resetPotionMerchant


bool Game::isWon() const {
    return won;
} // isWon


int Game::getScore() const {
    return pc->getScore();
} // getScore


bool Game::isLose() const {
    return pc->getHP() <= 0 ? true : false;
} // isLose


bool Game::isFloorChanged() const {
    return floorChanged;
} // isFloorChanged


void Game::init(GameNotification *notification) {
#ifdef DEBUG
    cout<<"entering game init mode"<<endl;
#endif
    clearGame();
#ifdef DEBUG
    cout<<"game cleared"<<endl;
#endif
    this->notification = notification;
    floor = new Cell*[rowNum * colNum];
    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            floor[i * colNum + j] = new Cell;
            (floor[i * colNum + j])->setGame(this);
            (floor[i * colNum + j])->setCoords(i, j);
            
            // add neighbours where appropriate
            if (j > 0) {
                (floor[i * colNum + j])->setNeighbour((floor[i * colNum + (j - 1)]), Cell::WEST);
                (floor[i * colNum + (j - 1)])->setNeighbour((floor[i * colNum + j]), Cell::EAST);
            } // if
            if (i > 0) {
                (floor[i * colNum + j])->setNeighbour((floor[(i - 1) * colNum + j]), Cell::NORTH);
                (floor[(i - 1) * colNum + j])->setNeighbour((floor[i * colNum + j]), Cell::SOUTH);
            } // IF
            if (i > 0 && j > 0) {
                (floor[i * colNum + j])->setNeighbour((floor[(i - 1) * colNum + (j - 1)]), Cell::NWEST);
                (floor[(i - 1) * colNum + (j - 1)])->setNeighbour((floor[i * colNum + j]), Cell::SEAST);
            } // if
            if (i > 0 && j < colNum - 1) {
                (floor[i * colNum + j])->setNeighbour((floor[(i - 1) * colNum + (j + 1)]), Cell::NEAST);
                (floor[(i - 1) * colNum + (j + 1)])->setNeighbour((floor[i * colNum + j]), Cell::SWEST);
            } // if
        } // for
    } // for
    return;
} // init(GameNotification)


NPC * Game::generateNPC(const char race) const {
    if (race == Character::HUMAN) {
        return new Human;
    } // if
    if (race == Character::DWARF) {
        return new Dwarf;
    } // if
    if (race == Character::ELF) {
        return new Elf;
    } // if
    if (race == Character::ORCS) {
        return new Orcs;
    } // if
    if (race == Character::MERCHANT) {
        return new Merchant;
    } // if
    if (race == Character::DRAGON) {
        return new Dragon;
    } // if
    if (race == Character::HALFLING) {
        return new Halfling;
    } // if
    return NULL;
} // generateNPC


void Game::init(int row, int col, char state) {
    // constants for gold
    const char normal = '6';
    const char small = '7';
    const char merchant = '8';
    const char dragonHrd = '9';
    
    // constants for potion
    const char lowerRange = '0';
    const char upperRange = '5';
    
    NPC *temp = NULL;
    
    if (state == normal) {
        (floor[row * colNum + col])->setState(new Gold(Gold::NORMAL));
        (floor[row * colNum + col])->setOrigin('.');
    } else if (state == small) {
        (floor[row * colNum + col])->setState(new Gold(Gold::SMALL));
        (floor[row * colNum + col])->setOrigin('.');
    } else if (state == merchant) {
        (floor[row * colNum + col])->setState(new Gold(Gold::MERCHANT));
        (floor[row * colNum + col])->setOrigin('.');
    } else if (state == dragonHrd) {
        DragonHoard *hoard = new DragonHoard;
        Dragon *dragon = floor[row * colNum + col]->scanForDragon();
        
        // link the dragonhoard with a dragon
        hoard->setDragon(dragon);
        if (dragon != NULL) {
            dragon->setHoard(hoard);
        } // if
        
        (floor[row * colNum + col])->setState(hoard);
        (floor[row * colNum + col])->setOrigin('.');
    } else if (state >= lowerRange && state <= upperRange) {
        (floor[row * colNum + col])->setState(new Potion(state));
        (floor[row * colNum + col])->setOrigin('.');
    } else if (state == '@') {
        if (pc == NULL) {
            pc = new Shade;
        } // if
        (floor[row * colNum + col])->setState(pc);
        (floor[row * colNum + col])->setOrigin('.');
    } else if (temp = generateNPC(state), temp != NULL) {
        
        // if it is a dragon, link it with a dragonhoard
        if (temp->getrace() == Character::DRAGON) {
            DragonHoard *hoard = floor[row * colNum + col]->scanForDHoard();
            static_cast<Dragon *>(temp)->setHoard(hoard);
            if (hoard != NULL) {
                // link
                hoard->setDragon(static_cast<Dragon *>(temp));
            } // if
        } // if
        
        (floor[row * colNum + col])->setState(temp);
        (floor[row * colNum + col])->setOrigin('.');
        npcTurns[temp] = 0;
    } else {
        (floor[row * colNum + col])->setState(state);
        (floor[row * colNum + col])->setOrigin(state);
    } // if. else if, else
} // init(int, int, string)


string Game::cmdToDirection(string cmd) {
    if (cmd == "nw") {
        return "North West";
    } // if
    if (cmd == "no") {
        return "North";
    } // if
    if (cmd == "ne") {
        return "North East";
    } // if
    if (cmd == "we") {
        return "West";
    } // if
    if (cmd == "ea") {
        return "East";
    } // if
    if (cmd == "sw") {
        return "South West";
    } // if
    if (cmd == "so") {
        return "South";
    } // if
    return "South East";
} // cmdToDirection


bool Game::chooseRace(char race) {
    // cannot choose again
    if (pc != NULL) {
        return false;
    } // if
    
    if (race == Character::SHADE) {
        pc = new Shade;
        notifyRace("Shade");
    } // if
    if (race == Character::DROW) {
        pc = new Drow;
        notifyRace("Drow");
    } // if
    if (race == Character::GOBLIN) {
        pc = new Goblin;
        notifyRace("Goblin");
    } // if
    if (race == Character::TROLL) {
        pc = new Troll;
        notifyRace("Troll");
    } // if
    if (race == Character::VAMPIRE) {
        pc = new Vampire;
        notifyRace("Vampire");
    } // if
    notifyAction("Player character has spawned.");
    return true;
} // chooseRace


PC * Game::clonePC(PC *original) {
    if (original->getrace() == Character::SHADE) {
        return new Shade(*static_cast<Shade *>(original));
    } // if
    if (original->getrace() == Character::DROW) {
        return new Drow(*static_cast<Drow *>(original));
    } // if
    if (original->getrace() == Character::VAMPIRE) {
        return new Vampire(*static_cast<Vampire *>(original));
    } // if
    if (original->getrace() == Character::TROLL) {
        return new Troll(*static_cast<Troll *>(original));
    } // if
    return new Goblin(*static_cast<Goblin *>(original));
} // clonePC


bool Game::playerMove(string direction) {
    // if player moved, it means floor must be properly initialized
    floorChanged = false;
    
    bool moveable = floor[playerRow * colNum + playerCol]->move(Cell::strToDirection(direction));
    if (moveable == false) {
        return false;
    } // if
    
    ++turnNum;
    
    if (playerPos == stairPos) {
        if (floorNum == maxFloorNum) {
            won = true;
        } // if
        
        if (won == false) {
            // should only call clonePC and clearGame when changing floor
            //   ,otherwise will cause memory leaks and/or memory errors
            pc = clonePC(pc);
            clearGame();
            
            ++floorNum;
            notifyFloor();
            floorChanged = true;
            string temp = "You entered floor ";
            temp.push_back(floorNum);
            temp += ".";
            notifyAction(temp);
        } // if
    } else {
        string temp = "PC moves ";
        temp += cmdToDirection(direction);
        temp +=".";
        notifyAction(temp);
    } // if ,else
    
    return true;
} // playerMove


bool Game::playerAtk(string direction) {
    bool temp = floor[playerRow * colNum + playerCol]->attack(Cell::strToDirection(direction));
    if (temp == true) {
        ++turnNum;
    } // if
    return temp;
} // playerAtk


bool Game::consumePotion(string direction) {
    bool temp = floor[playerPos]->consumePotion(Cell::strToDirection(direction));
    if (temp == true) {
        ++turnNum;
    } // if
    return temp;
} // consumePotion


void Game::endTurn() {
    
    // invoke npcs around pc to attack pc
    floor[playerPos]->NPCAroundAtk(npcTurns, turnNum); 

    // scan around pc for potions
    floor[playerPos]->scanForPotion();

    if (pc->getrace() == Character::TROLL && pc->getHP() < pc->getMaxHP() && pc->getHP() > 0) {
        pc->race_special();
        notification->notifyHP(pc->getHP());
        notification->notifyAction("PC regenerates 5 HP (Troll).");
    } // if

    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            Cell &cur = *(floor[i * colNum + j]);
            // if the NPC has not used its turn
            if (cur.isNPC() == true && npcTurns[cur.getNPC()] < turnNum) {
                
                ++npcTurns[cur.getNPC()];
                
                // if it is not a dragon, then it can move
                if (cur.isDragon() == false) {
                    Cell::Direction dir;

                    // if there exists a valid move for this NPC
                    if (cur.scanForNPCmove()) {
                        // loop until finds a valid position to move
                        while (dir = static_cast<Cell::Direction>(rand() % Cell::NO_DIR), cur.move(dir) == false) {}
                    } // if
                } // if
            } // if
        } // for
    } // for
} // endTurn


void Game::scanPotion() const {
    floor[playerPos]->scanForPotion();
} // scanPotion
