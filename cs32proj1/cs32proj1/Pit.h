//
//  Pit.h
//  cs32proj1
//
//  Created by Cici Ni on 1/11/15.
//  Copyright (c) 2015 Cici Ni. All rights reserved.
//

#ifndef cs32proj1_Pit_h
#define cs32proj1_Pit_h
#include "globals.h"
#include "History.h"
#include <string>

class Player;
class Snake;
class Pit
{
public:
    // Constructor/destructor
    Pit(int nRows, int nCols);
    ~Pit();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     snakeCount() const;
    int     numberOfSnakesAt(int r, int c) const;
    void    display(std::string msg) const;
    
    // Mutators
    bool   addSnake(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyOneSnake(int r, int c);
    bool   moveSnakes();
    
    History& history();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Snake*  m_snakes[MAXSNAKES];
    int     m_nSnakes;
    
    History  m_history;
};


#endif
