//
//  cell.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-14.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__cell__
#define __cc3k__cell__

#include <map>
#include <string>
#include "gold.h"
#include "potion.h"
#include "pc.h"
#include "npc.h"
#include "character.h"

class Dragon;
class DragonHoard;
class Game;

class Cell {
    int r, c;       // row and col of cell position
    char originState;
    char state;
    Game *game;
    PC *pc;
    NPC *npc;
    Gold *gold;
    Potion *potion;
    static const int maxNeighbours = 8;
    Cell *neighbours[maxNeighbours];
    
    void notifyGame() const;
    void notifyGameAction(std::string action) const;
    
    
public:
    Cell();         // default ctor
    ~Cell();        // default dtor
    
    void notifyGamePC() const;
    
    enum FloorTile {UNOCCUPIED = '.', DOOR = '+', STAIR = '\\', PATH = '#', VAIN = ' '};
    enum Direction {NWEST, NORTH, NEAST, WEST, EAST, SWEST, SOUTH, SEAST, NO_DIR};
    
    /* reverse the direction passed in
        e.g. Cell::NWEST -> Cell::SEAST
             Cell::EAST -> Cell::WEST
     */
    static Cell::Direction reverseDir(Cell::Direction dir);
    
    /* transforms string cmd direction to Cell's enum
        eg. no -> Cell::NORTH
            se -> Cell::SEAST
     */
    static Cell::Direction strToDirection(std::string direction);
    /* transforms Cell's enum to string direction
     eg. Cell::NORTH -> North
         Cell::SEAST -> South East
     */
    static std::string directionToStr(Direction direction);
    
    void setCoords(int row, int col);
    void setGame(Game *g);
    void setOrigin(char origin);        // set the original state of this cell
    void setNeighbour(Cell *neighbour, Direction dir);   // set the neighbour of a particular direction
    void setUnoccupied();                    // clear any object in this cell
    void setState(char state);      // ONLY FOR FIRST STAGE
    char getState() const;
    bool isUnoccupied() const;      // return true for unoccupied plain normal floor tile
    bool isPC() const;
    bool isNPC() const;             //
    bool isDragon() const;
    bool isPotion() const;
    bool isGold() const;
    bool isDragonHoard() const;
    bool isPCMovable() const;         // return true for cell that player can move in
    void setState(Gold *g);
    void setState(Potion *p);
    void setState(PC *c);
    void setState(NPC *c);
    PC *getPC() const;
    NPC *getNPC() const;
    Potion *getPotion() const;
    Gold *getGold() const;
    bool move(Direction dir);
    bool attack(Direction dir);
    bool consumePotion(Direction dir);
    void NPCAroundAtk(std::map<NPC *, unsigned int> &npcTurns, unsigned int turnNum);    // invoke in-range hostile npc to attack player, update npcTurns accordingly
    
    // scan around PC's position for potion info, and notify game
    void scanForPotion();
    
    // scan around the position, and return the first unlinked dragon, otherwise return NULL
    Dragon *scanForDragon() const;
    
    // scan around the position, and return the first unlinked dragonHoard, otherwise return NULL
    DragonHoard *scanForDHoard() const;

    // scan around the position, and return false if it is surrounded by unmovable cells by NPC, true otherwise
    bool scanForNPCmove() const;
};

#endif /* defined(__cc3k__cell__) */
