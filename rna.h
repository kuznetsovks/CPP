#pragma once
#include "reference.h"
#include <utility>
#include <exception>
#include <bitset>
#include <unordered_map>

class Reference;

class RNA
{

public:
    friend class Reference;
    size_t cross=sizeof(size_t)/2*8;
    size_t contsize;
    size_t capacity;
    size_t blocks;
    size_t* cont;

    RNA();
    RNA(Nucl,size_t);
    ~RNA();
    RNA(const RNA&);
    size_t* createRNA(size_t);
    size_t cardinality(Nucl);
    RNA& operator=(const RNA&);
    bool operator!=(const RNA&);
    bool operator==(const RNA&);
    Reference operator[](size_t);
    friend RNA operator+(const RNA &,const RNA &);
};
