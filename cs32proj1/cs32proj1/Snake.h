//
//  Snake.h
//  cs32proj1
//
//  Created by Cici Ni on 1/11/15.
//  Copyright (c) 2015 Cici Ni. All rights reserved.
//

#ifndef cs32proj1_Snake_h
#define cs32proj1_Snake_h
class Pit;

class Snake
{
public:
    // Constructor
    Snake(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};


#endif
