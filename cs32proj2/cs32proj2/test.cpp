//
//  test.cpp
//  cs32proj2
//
//  Created by Cici Ni on 1/26/15.
//  Copyright (c) 2015 Cici Ni. All rights reserved.
//

#include <stdio.h>
#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Multiset sms;
    assert(sms.size() == 0);          // test o size
    assert(sms.empty());              // test empty
    assert(sms.erase("cumin") == 0);  // nothing to erase
    assert(sms.insert("cumin"));      //test insert
    assert(sms.insert("turmeric"));
    assert(sms.insert("cumin"));
    assert(sms.insert("coriander"));
    assert(sms.insert("cumin"));
    assert(sms.insert("turmeric"));
    assert(sms.size() == 6  &&  sms.uniqueSize() == 3);
    assert(sms.count("turmeric") == 2);
    assert(sms.count("cumin") == 3);
    assert(sms.count("coriander") == 1);
    assert(sms.count("cardamom") == 0);
    assert(sms.erase("turmeric"));    //test earase
    assert(sms.count("turmeric") == 1);
    assert(sms.eraseAll("cumin"));    //test eraseAll
    assert(sms.count("cumin") == 0);
}

void test2()
{
    Multiset ms;
    ms.insert("cinnamon");
    ms.insert("galangal");
    ms.insert("cinnamon");
    string s1;
    int n1 = ms.get(1, s1);
    assert((s1 == "cinnamon"  &&  n1 == 2)  ||  (s1 == "galangal"  &&  n1 == 1));
    string s2;
    int n2 = ms.get(1, s2);
    assert(s2 == s1  &&  n2 == n1);
}

void test3()
{
    Multiset ms1;
    ms1.insert("cumin");
    ms1.insert("cumin");
    ms1.insert("cumin");
    ms1.insert("turmeric");
    Multiset ms2;
    ms2.insert("coriander");
    ms2.insert("cumin");
    ms2.insert("cardamom");
    ms1.swap(ms2);  // exchange contents of ms1 and ms2
    assert(ms1.size() == 3  &&  ms1.count("coriander") == 1  &&
           ms1.count("cumin") == 1  &&  ms1.count("cardamom") == 1);
    assert(ms2.size() == 4  &&  ms2.count("cumin") == 3  &&
           ms2.count("turmeric") == 1);
}

void test4()
{
    Multiset ms;
    ms.insert("cumin");
    assert(!ms.contains(""));
    ms.insert("nutmeg");
    ms.insert("");
    ms.insert("saffron");
    assert(ms.contains(""));
    ms.erase("cumin");
    assert(ms.size() == 3  &&  ms.contains("saffron")  &&  ms.contains("nutmeg")  &&
           ms.contains(""));
}



int main()
{
    test();
    test2();
    test3();
    test4();
    cout << "Passed all tests" << endl;
}