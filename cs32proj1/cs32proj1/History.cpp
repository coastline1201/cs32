//
//  History.cpp
//  cs32proj1
//
//  Created by Cici Ni on 1/11/15.
//  Copyright (c) 2015 Cici Ni. All rights reserved.
//
#include <iostream>
#include <cstdlib>
using namespace std;
#include "History.h"
#include "globals.h"

History::History(int nRows, int nCols)
: m_nRows(nRows), m_nCols(nCols)
{
    int i,j;
    for (i=0;i<m_nRows;i++)
        for (j=0; j<m_nCols; j++)
            m_historyGrid[i][j]=0;
        
}

bool History::record(int r, int c)
{
    if (r<1||r>m_nRows||c<1||c>m_nCols) {
        return false;
    }
    m_historyGrid[r-1][c-1]+=1;
    return true;
    
}

void History::display() const
{
    char display[MAXROWS][MAXCOLS];
    int i,j;
    
    clearScreen();
    for (i=0; i<m_nRows; i++) {
        for (j=0; j<m_nCols; j++) {
            if (m_historyGrid[i][j]==0)
                display[i][j]='.';
                else if (m_historyGrid[i][j]>=26)
                    display[i][j]='z';
                else display[i][j]=m_historyGrid[i][j]+64;
            
            cout<<display[i][j];
            
        }
        cout<<endl;
    }
    cout<<endl;
    
   
}
