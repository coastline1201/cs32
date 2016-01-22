//
//  History.h
//  cs32proj1
//
//  Created by Cici Ni on 1/11/15.
//  Copyright (c) 2015 Cici Ni. All rights reserved.
//

#ifndef __cs32proj1__History__
#define __cs32proj1__History__

#include <stdio.h>
#include "globals.h"
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_nRows;
    int m_nCols;
    int m_historyGrid[MAXROWS][MAXCOLS];
};

#endif /* defined(__cs32proj1__History__) */
