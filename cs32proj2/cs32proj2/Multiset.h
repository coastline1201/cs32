//
//  Multiset.h
//  cs32proj2
//
//  Created by Cici Ni on 1/25/15.
//  Copyright (c) 2015 Cici Ni. All rights reserved.
//

#ifndef __cs32proj2__Multiset__
#define __cs32proj2__Multiset__

#include <stdio.h>
#include <iostream>
#include <string>
#include "OurType.h"

typedef OurType ItemType;

class Multiset
{
public:
    Multiset();
    bool empty() const;
    int size() const;
    int uniqueSize() const;
    bool insert(const ItemType& value);
    int erase(const ItemType& value);
    int eraseAll(const ItemType& value);
    bool contains(const ItemType& value) const;
    int count(const ItemType& value) const;
    int get(int i, ItemType& value) const;
    void swap(Multiset& other);
    ~Multiset(); //destructor
    Multiset(const Multiset& other); //copy constructor
    Multiset& operator=(const Multiset& rhs); //assignment operator
private:
    struct Node{
        ItemType data;
        int count;
        Node* next;
        Node* prev;
    };
    int m_size;
    int m_uniqueSize;
    Node* head;
    
};

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);

#endif /* defined(__cs32proj2__Multiset__) */
