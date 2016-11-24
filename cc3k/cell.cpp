//
//  cell.cpp
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-14.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "gold.h"
#include "dragonhoard.h"
#include "cell.h"
#include "game.h"
#include "dragon.h"

using namespace std;

Cell::Cell() {
    originState = VAIN;
    state = VAIN;
    game = NULL;
    pc = NULL;
    npc = NULL;
    gold = NULL;
    potion = NULL;
    for (int i = 0; i < maxNeighbours; ++i) {
        neighbours[i] = NULL;
    } // for
} // default ctor


Cell::~Cell() {
    delete gold;
    delete potion;
    delete npc;
    delete pc;
}


void Cell::notifyGame() const {
    game->notify(r, c, state);
} // notifyGame


void Cell::notifyGamePC() const {
    if (pc != NULL) {
        game->notifyHP(pc->getHP());
        game->notifyGold(pc->getgold());
        game->notifyAtk(pc->getAtk());
        game->notifyDef(pc->getDef());
    } // if
} // notifyGamePC


void Cell::notifyGameAction(string action) const {
    game->notifyAction(action);
} // notifyGameAction


void Cell::setCoords(int row, int col) {
    r = row;
    c = col;
} // setCoords


void Cell::setGame(Game *g) {
    game = g;
} // setGame


void Cell::setOrigin(char origin) {
    originState = origin;
} // setOrigin


void Cell::setNeighbour(Cell *neighbour, Direction dir) {
    neighbours[dir] = neighbour;
} // setNeighbour


void Cell::setUnoccupied() {
    state = originState;
    pc = NULL;
    npc = NULL;
    gold = NULL;
    potion = NULL;
    notifyGame();
} // setEmpty


void Cell::setState(char state) {
    this->state = state;
    notifyGame();
} // setState


char Cell::getState() const {
    return state;
} // getState


bool Cell::isUnoccupied() const {
    return state == UNOCCUPIED ? true : false;
} // isUnoccupied


bool Cell::isPC() const {
    return pc != NULL ? true : false;
} // isPC


bool Cell::isNPC() const {
    return npc != NULL ? true : false;
} // isNPC


bool Cell::isDragon() const {
    if (isNPC() == false) {
        return false;
    } // if
    return npc->getrace() == Character::DRAGON ? true : false;
} // isDragon


bool Cell::isPotion() const {
    return potion != NULL ? true : false;
} // isPotion


bool Cell::isGold() const {
    return gold != NULL ? true : false;
} // isGold


bool Cell::isDragonHoard() const {
    if (isGold() == false) {
        return false;
    } // if
    return gold->getValue() == Gold::DRAGON ? true : false;
} // isDragonHoard


bool Cell::isPCMovable() const {
    // if this cell has a gold
    if (state == 'G') {
        return gold->pickable();
    } // if
    
    if (state == UNOCCUPIED || state == DOOR || state == STAIR || state == PATH) {
        return true;
    } // if
    return false;
} // isPCMovable


void Cell::setState(Gold *g) {
    gold = g;
    state = 'G';
    notifyGame();
} // setState(Gold)


void Cell::setState(Potion *p) {
    potion = p;
    state = 'P';
    notifyGame();
} // setState(Potion)


void Cell::setState(PC *c) {
    pc = c;
    state = '@';
    notifyGame();
    notifyGamePC();
} // setState(Character)


void Cell::setState(NPC *c) {
    npc = c;
    state = c->getrace();
    notifyGame();
} // setState(Character)


PC * Cell::getPC() const {
    return pc;
} // getPC


NPC * Cell::getNPC() const {
    return npc;
} // getNPC


Potion * Cell::getPotion() const {
    return potion;
} // getPotion


Gold * Cell::getGold() const {
    return gold;
} // getGold


bool Cell::move(Direction dir) {
    Cell &dest = *(neighbours[dir]);
    if (pc != NULL) {
        // if pc cannot move to dest (invalid terrain or dragonhoard protected by dragon)
        if (!dest.isPCMovable()) {
            return false;
        } // if
        // if there is a gold in the dest, then pc pickup the gold
        if (dest.getState() == 'G') {
            pc->addGold(dest.getGold());
            notifyGamePC();
            
            // block of code for synthesize 'pc picks gold' action message and notify the game. BLOCK BEGINS
            stringstream stream;
            string action = "PC picks up ";
            string numStr;
            stream<<(dest.getGold()->getValue());
            stream>>numStr;
            action += numStr;
            action += " gold.";
            notifyGameAction(action);
            // BLOCK ENDS
            
            delete dest.getGold();
            dest.setUnoccupied();
        } // if
        dest.setState(pc);
        setUnoccupied();
        return true;
    } else if (npc != NULL) {
        if (dest.isUnoccupied() == false || isDragon() == true) {
            return false;
        } // if
        dest.setState(npc);
        setUnoccupied();
        return true;
    } // if, else if
    return false;
} // move


bool Cell::attack(Direction dir) {
    Cell &dest = *(neighbours[dir]);
    if (isPC() == true) {
        if (dest.isNPC() == false) {
            return false;
        } // if
        
        // block of code for synthesize 'pc attacks npc' action message and notify the game. BLOCK BEGINS
        stringstream stream;
        const int damage = pc->attack(*(dest.getNPC()));
        // notifyGamePC in case PC is a vampire
        notifyGamePC();
        if (damage == -1) {
            string action = "PC attacks, but it missed.";
            notifyGameAction(action);
            return true;
        } // if
        stream<<damage;
        string numStr;
        stream>>numStr;
        string action = "PC deals " + numStr + " damage to ";
        action.push_back(static_cast<char>(dest.getNPC()->getrace()));
        
        if (pc->getrace() == Character::VAMPIRE) {
            if (dest.getNPC()->getrace() == Character::DWARF) {
                notifyGameAction("Allergic to W, lose 5 HP.");
            } else {
                notifyGameAction("PC sucks 5 HP (Vampire).");
            } // if, else
        } // if

        // reset stream
        stream.str("");
        stream.seekg(0);
        stream.seekp(0);
    
        stream<<(dest.getNPC()->getHP());
#ifdef DEBUG
        cout<<"remaining npc hp "<<dest.getNPC()->getHP()<<endl;
#endif
        stream>>numStr;
        action += " (" + numStr + " HP).";
        notifyGameAction(action);
        // BLOCK ENDS
        
        // if the defender is dead
        if ((dest.getNPC())->getHP() <= 0) {
            
            // synthesize 'npc is killed' message, and notify game
            action = static_cast<char>(dest.getNPC()->getrace());
            action += " is slain.";
            notifyGameAction(action);
            
            // if it is not dragon, then loot the npc, synthesize action message, and notifyGame
            if (dest.isDragon() == false) {
                // block of code for synthesize 'pc loots gold' action message and notify the game. BLOCK BEGINS
                
                // reset stream
                stream.str("");
                stream.seekg(0);
                stream.seekp(0);
                
                // Goblin gets 5 more
                if (pc->getrace() == Character::GOBLIN) {
                  stream<<(dest.getNPC()->gold_hold()->getValue() + 5);
                } else {
                  stream<<(dest.getNPC()->gold_hold()->getValue());
                } // if, else

                stream>>numStr;
                action = "PC loots " + numStr + " gold from ";
                action.push_back(static_cast<char>(dest.getNPC()->getrace()));
                action += ".";
                notifyGameAction(action);
                // BLOCK ENDS
                
                
                pc->addGold(dest.getNPC());
                notifyGamePC();
            } // if
            
            delete  dest.getNPC();
            dest.setUnoccupied();
        } // if
#ifdef DEBUG
        cout<<endl;
#endif
        return true;
    } else if (isNPC() == true) {
        if (dest.isPC() == false) {
            return false;
        } // if
        if (dest.getPC()->getHP() <= 0) {
            return false;
        } // if
        
        // block of code for synthesize 'npc attacks pc' action message and notify the game. BLOCK BEGINS
        stringstream stream;
        const int damage = npc->attack(*(dest.getPC()));
        if (damage == -1) {
            string action;
            action.push_back(static_cast<char>(npc->getrace()));
            action += " attacks, but it missed.";
            notifyGameAction(action);
            return true;
        } // if
        stream<<damage;
        string numStr;
        stream>>numStr;
        string action = "";
        action.push_back(static_cast<char>(npc->getrace()));
        action += " deals " + numStr + " damage to PC.";
        dest.notifyGamePC();
        notifyGameAction(action);
        // BLOCK ENDS
        
        
#ifdef DEBUG
        cout<<endl;
#endif
        return true;
    } else if (isDragonHoard() == true) {
        // block of code for synthesize 'dragon attacks pc' action message and notify the game. BLOCK BEGINS
        stringstream stream;
        const int damage = static_cast<DragonHoard *>(gold)->notifyDragon(*(dest.getPC()));
        if (damage == -1) {
            string action = "D attacks, but it missed.";
            notifyGameAction(action);
            return true;
        } // if
        stream<<damage;
        string numStr;
        stream>>numStr;
        string action = "";
        action.push_back(static_cast<char>(Character::DRAGON));
        action += " deals " + numStr + " damage to PC.";
        dest.notifyGamePC();
        notifyGameAction(action);
        // BLOCK ENDS

    }
    return false;
} // attack


bool Cell::consumePotion(Cell::Direction dir) {
    if (pc == NULL) {
        return false;
    } // if
    // if there is no potion in the specified direction
    if (neighbours[dir]->isPotion() == false) {
        return false;
    } // if
    Potion &p = *(neighbours[dir]->getPotion());
    pc = pc->consume_potion(p);
    notifyGamePC();
    
    // synthesize action message and notify game
    string action;
    action = "PC uses " + Potion::effectToStr(p.getEffect()) + ".";
    notifyGameAction(action);
    
    delete &p;
    neighbours[dir]->setUnoccupied();
    return true;
} // consumePotion


Cell::Direction Cell::reverseDir(Cell::Direction dir) {
    /* the first dir is the revserve of last
            second dir is the reverse of second last
            and so on
     */
    return static_cast<Cell::Direction>(NO_DIR - 1 - dir);
} // reverseDir


Cell::Direction Cell::strToDirection(string direction) {
    if (direction == "nw") {
        return Cell::NWEST;
    } // if
    if (direction == "no") {
        return Cell::NORTH;
    } // if
    if (direction == "ne") {
        return Cell::NEAST;
    } // if
    if (direction == "we") {
        return Cell::WEST;
    } // if
    if (direction == "ea") {
        return Cell::EAST;
    } // if
    if (direction == "sw") {
        return Cell::SWEST;
    } // if
    if (direction == "so") {
        return Cell::SOUTH;
    } // if
    return Cell::SEAST;
} // strToDirection


string Cell::directionToStr(Cell::Direction direction) {
    if (direction == NWEST) {
        return "North West";
    } // if
    if (direction == Cell::NORTH) {
        return "North";
    } // if
    if (direction == Cell::NEAST) {
        return "North East";
    } // if
    if (direction == Cell::WEST) {
        return "West";
    } // if
    if (direction == Cell::EAST) {
        return "East";
    } // if
    if (direction == Cell::SWEST) {
        return "South West";
    } // if
    if (direction == Cell::SOUTH) {
        return "South";
    } // if
    return "South East";
} // directionToStr


void Cell::NPCAroundAtk(map<NPC *, unsigned int> &npcTurns, unsigned int turnNum) {
    if (pc != NULL) {
        for (int i = 0; i < maxNeighbours; ++i) {
            Cell &cur = *(neighbours[i]);
            if (cur.isNPC() && cur.getNPC()->isHostile() && npcTurns[cur.getNPC()] < turnNum) {
                cur.attack(reverseDir(static_cast<Cell::Direction>(i)));     // commence attack
                
#ifdef DEBUG
                cout<<"PC is under attack!"<<endl;
#endif
                
                // if the npc is elf and pc is not drow, then attacks twice
                if (cur.getNPC()->getrace() == Character::ELF && pc->getrace() != Character::DROW) {
                    notifyGameAction("E attacks twice to non-Drow PC.");
                    cur.attack(reverseDir(static_cast<Cell::Direction>(i)));
                } // if
                
                ++npcTurns[cur.getNPC()];     // update npcTurn
            } else if (cur.isDragonHoard() && !(static_cast<DragonHoard *>(cur.getGold())->pickable())) {
                Dragon *tempDragon = static_cast<DragonHoard *>(cur.getGold())->getDragon();
                if (npcTurns[tempDragon] >= turnNum) {
                    break;
                } // if
                
                cur.attack(reverseDir(static_cast<Cell::Direction>(i)));     // commence attack
                
#ifdef DEBUG
                cout<<"PC is under attack!"<<endl;
#endif
                
                ++npcTurns[tempDragon];     // update dragon's turn
            } // if, else if
        } // for
    } // if
    
    return;
} // NPCAroundAtk


void Cell::scanForPotion() {
    string action;
    for (int i = 0; i < maxNeighbours; ++i) {
        if (neighbours[i] != NULL && neighbours[i]->isPotion() == true) {
            const Potion &p = *(neighbours[i]->getPotion());
            
            // insert a single space between sentences
            if (action.length() != 0) {
                action += " ";
            } // if
            if (p.isVisible() == true) {
                action += Potion::effectToStr(p.getEffect());
            } else {
                action += "Unknown";
            } // if, else
            action += " potion at " + directionToStr(static_cast<Direction>(i));
            action += ".";
        } // if
    } // for
    
    // if action message is not empty
    if (action.length() != 0) {
        notifyGameAction(action);
    } // if
} // scanForPotion


Dragon * Cell::scanForDragon() const {
    for (int i = 0; i < maxNeighbours; ++i) {
        if (neighbours[i]->isDragon() == true && static_cast<Dragon *>(neighbours[i]->getNPC())->hasHoard() == false) {
            return static_cast<Dragon *>(neighbours[i]->getNPC());
        } // if
    } // for
    return NULL;
} // scanForDragon


DragonHoard * Cell::scanForDHoard() const {
    for (int i = 0; i < maxNeighbours; ++i) {
        if (neighbours[i]->isDragonHoard() == true && neighbours[i]->getGold()->pickable() == true) {
            return static_cast<DragonHoard *>(neighbours[i]->getGold());
        } // if
    } // for
    return NULL;
} // scanForDHoard


bool Cell::scanForNPCmove() const {
    for (int i = 0; i < maxNeighbours; ++i) {
        if (neighbours[i]->isUnoccupied()) {
            return true;
        } // if
    } // for
    return false;
} // scanForNPCmove
