//
//  Multiset.cpp
//  cs32proj2
//
//  Created by Cici Ni on 1/25/15.
//  Copyright (c) 2015 Cici Ni. All rights reserved.
//

#include "Multiset.h"

Multiset::Multiset()
{
    m_size=0;
    m_uniqueSize=0;
    head=new Node;
    head->next=nullptr;
    head->prev=nullptr;
}

Multiset::~Multiset()
{
    if (head!=nullptr)
    {
    Node* p=head->next;
    //delete the node one by one
    while (p!=nullptr) {
        head->next=p->next;
        delete p;
        p=head->next;
    }
    
    delete head;
    }
}
Multiset::Multiset(const Multiset& other)
{
    m_size=other.m_size;
    m_uniqueSize=other.m_uniqueSize;
    
    //copy the head
    head=new Node;
    head->data=other.head->data;
    head->count=other.head->count;
    head->prev=nullptr;
    
    //copy the rest of the list
    Node* p=head;
    Node* pOther=other.head->next;
    while (pOther!=nullptr) {
        p->next=new Node;
        p->next->data=pOther->data;
        p->next->count=pOther->count;
        p->next->prev=p;
        p=p->next;
        pOther=pOther->next;
        
    }
    p->next=nullptr;
    
}
Multiset& Multiset::operator=(const Multiset& rhs)
{
    if (this != &rhs)
    {
        Multiset temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Multiset::empty() const
{
    return size()==0;
}
int Multiset::size() const
{
    return m_size;
}
int Multiset::uniqueSize() const
{
    return m_uniqueSize;
}
bool Multiset::insert(const ItemType& value)
{
    //deal with empty list, insert the head node with value
    if (empty()) {
        head->data=value;
        head->count=1;
        m_size++;
        m_uniqueSize++;
        return true;
    }
    
    //find out whether the value is already there
    Node *p,*prev1 = nullptr;
    for (p=head; p!=nullptr; p=p->next) {
        prev1=p;
        if (value==p->data) {
            p->count++;
            m_size++;
            return true;
        }
    }
    
    //if the value is not there, add a new node
    p=new Node;
    p->data=value;
    p->count=1;
    p->next=nullptr;
    p->prev=prev1;
    prev1->next=p;
    m_size++;
    m_uniqueSize++;
    return true;
    
}
int Multiset::erase(const ItemType& value)
{
      //deal with empty list
    if (empty()) {
        return 0;
    }
   
    //check if the value is in the list
    for (Node* p=head; p!=nullptr; p=p->next) {
        if (value==p->data) {
            //delete the value once
            p->count--;
            m_size--;
            if (p->count==0) {
                //if count is zero, delete the node containing the value
                m_uniqueSize--;
                if (p==head) {
                    head=p->next;
                    if (head!=nullptr)
                       head->prev=nullptr;
                }
                else
                {
                    p->prev->next=p->next;
                    if (p->next!=nullptr)
                        p->next->prev=p->prev;
                }
                delete p;
            }
            return 1;
        }
    }
    return 0;
    
}
int Multiset::eraseAll(const ItemType& value)
{
      //deal with empty list
    if (empty()) {
        return 0;
    }
    
    //check if the value is in the list
    for (Node* p=head; p!=nullptr; p=p->next) {
        if (value==p->data) {
            //delete the node containing the value
            int countDel=p->count;
            m_size-=countDel;
            m_uniqueSize--;
            if (p==head) {
                head=p->next;
                head->prev=nullptr;
            }
            else
            {
                p->prev->next=p->next;
                if (p->next!=nullptr)
                    p->next->prev=p->prev;
            }
            delete p;
            
            return countDel;
        }
    }
    return 0;

}
bool Multiset::contains(const ItemType& value) const
{
      //deal with empty list
    if (empty()) {
        return false;
    }
    
    for (Node* p=head; p!=nullptr; p=p->next) {
        if (value==p->data) {
            return true;
        }
    }
    return false;
}
int Multiset::count(const ItemType& value) const
{
      //deal with empty list
    if (empty()) {
        return 0;
    }
    for (Node* p=head; p!=nullptr; p=p->next) {
        if (value==p->data) {
            return p->count;
        }
    }
    return 0;

}
int Multiset::get(int i, ItemType& value) const
{
      //deal with empty list
    if (empty()) {
        return 0;
    }
    
    //check if i is in the proper range
    if (i>=0&&i<m_uniqueSize) {
        int pos=0;
        //retrive the desired node in a consistent order
        for (Node* p=head; p!=nullptr; p=p->next) {
            if (pos==i) {
                value=p->data;
                return p->count;
            }
            pos++;
        }
    
    
    }
    return 0;
}
void Multiset::swap(Multiset& other)
{
    int Temp;
    Node* headTemp;
    
    Temp=m_size;
    m_size=other.m_size;
    other.m_size=Temp;
    
    Temp=m_uniqueSize;
    m_uniqueSize=other.m_uniqueSize;
    other.m_uniqueSize=Temp;
    
    //swap the head of 2 multies would be sufficient
    headTemp=head;
    head=other.head;
    other.head=headTemp;

}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    Multiset ms(ms1);
    int addCount;
    ItemType addValue;
    //for every value in ms2, insert into ms1 one by one
    for (int i=0; i<ms2.uniqueSize(); i++) {
        addCount=ms2.get(i, addValue);
        for (int j=0; j<addCount; j++) {
            ms.insert(addValue);
        }
    }
    result=ms;
}
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    Multiset ms(ms1);
    int subCount;
    ItemType subValue;
    //for every value in ms2, subtract from ms1 one by one
    for (int i=0; i<ms2.uniqueSize(); i++) {
        subCount=ms2.get(i, subValue);
        for (int j=0; j<subCount; j++) {
            ms.erase(subValue);
        }
    }
    result=ms;

}

