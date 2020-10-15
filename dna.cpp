#pragma once
#include <cmath>
#include "dna.h"
#include <iostream>
using namespace std;
DNA::DNA( RNA& a, RNA& b)
{
    if (a.isComplementary(b)==true)
    {
        dna = make_pair(a,b);
    }
}
    void DNA::print(){
    cout<<"First RNA in DNA:"<<endl;
    for (size_t i = 0; i < ceil(dna.first.contsize/16.0); i++) {
    cout << bitset<sizeof(dna.first.cont[i])* CHAR_BIT>(dna.first.cont[i]) << endl;
	}
    cout<<"Second RNA in DNA:"<<endl;
    for (size_t i = 0; i < ceil(dna.second.contsize/16.0); i++) {
    cout << bitset<sizeof(dna.second.cont[i])* CHAR_BIT>(dna.second.cont[i]) << endl;
	}
    }


