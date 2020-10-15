#pragma once
#include "rna.h"
using namespace std;
class DNA
{
public:
    size_t pairsize;
    pair<RNA,RNA> dna;

    DNA( RNA&, RNA&);
    void print();
};
