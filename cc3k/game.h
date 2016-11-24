//
//  game.h
//  cc3k
//
//  Created by Tianyi Ben on 2015-07-14.
//  Copyright (c) 2015 Tianyi Ben. All rights reserved.
//

#ifndef __cc3k__game__
#define __cc3k__game__

#include <string>
#include <map>
#include "cell.h"

class PC;

/*
 * Abstract class to allow Game to send noticiations
 * to a registered object
 */
class GameNotification {
public:
    virtual void notify(int r, int c, char state) = 0;
    virtual void notifyRace(std::string race) = 0;
    virtual void notifyGold(int gold) = 0;
    virtual void notifyHP(int HP) = 0;
    virtual void notifyAtk(int Atk) = 0;
    virtual void notifyDef(int Def) = 0;
    virtual void notifyAction(std::string action) = 0;
    virtual void notifyFloor(char floor) = 0;
    
};


class Game {
    Cell **floor;
    GameNotification *notification;
    PC *pc;
    unsigned int turnNum;        // number of turns played
    char floorNum;       // current floor number
    int playerRow, playerCol, playerPos;       // player's location
    int stairRow, stairCol, stairPos;
    bool floorChanged;      // if there is a floor change just occured
    const char maxFloorNum;
    bool won;               // if the game is won
    static const int rowNum;        // number of rows in total
    static const int colNum;        // number of cols in total
    
    void notifyFloor();
    void notifyRace(std::string race);
    
    std::map<NPC *, unsigned int> npcTurns;
    
    std::string cmdToDirection(std::string cmd);
    
    PC * clonePC(PC *original);
    
    NPC *generateNPC(const char race = '\0') const;
    
    void clearGame();       // Frees the floor
public:
    Game();     // default ctor
    ~Game();    // default dtor
    
    void notify(int row, int col, char change);
    void notifyGold(int gold);
    void notifyHP(int HP);
    void notifyAtk(int Atk);
    void notifyDef(int Def);
    void notifyAction(std::string action);
    
    void resetPotionMerchant();
    bool isWon() const;
    int getScore() const;
    bool isLose() const;
    bool isFloorChanged() const;
    void init(GameNotification *notification);      // Sets up the floor.  Clears old floor, if necessary.
    void init(int row, int col, char s);    // used when floor layout passed in
    bool chooseRace(char race);     // return true on success, and false otherwise
    bool playerMove(std::string direction);     // return true on succeed, false otherwise
    bool playerAtk(std::string direction);      // return true on valid attack, false otherwise
    bool consumePotion(std::string direction);
    void endTurn();         // called upon player's turn ends
    void scanPotion() const;      // called by controller after entering a new floor
};

#endif /* defined(__cc3k__game__) */
