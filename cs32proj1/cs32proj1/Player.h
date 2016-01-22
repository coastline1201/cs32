//
//  Player.h
//  cs32proj1
//
//  Created by Cici Ni on 1/11/15.
//  Copyright (c) 2015 Cici Ni. All rights reserved.
//

#ifndef cs32proj1_Player_h
#define cs32proj1_Player_h

class Pit;
class Player
{
public:
    // Constructor
    Player(Pit *pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   move(int dir);
    void   setDead();
    
private:
    Pit*  m_pit;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

#endif
