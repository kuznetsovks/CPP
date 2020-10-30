#pragma once
#include "reference.h"
#include <utility>
#include <exception>
#include <bitset>
#include <unordered_map>
using namespace std;
class Reference;

class RNA
{
private:
    size_t cross = sizeof(size_t) / 2 * 8;
    size_t capacity;
    size_t blocks;
    size_t* createRNA(size_t);
public:
    friend class Reference;
    size_t contsize;
    size_t* cont;

    RNA();
    RNA(Nucl,size_t);
    ~RNA();
    RNA(const RNA&);

    size_t cardinality(Nucl) const;
    RNA& operator=(const RNA&);
    RNA& operator!();
    bool operator!=(const RNA&) const;
    bool operator==(const RNA&) const;
    bool isComplementary (RNA&) const;
    RNA& split(size_t,bool );
    Reference operator[](size_t);
    friend RNA operator+(const RNA &,const RNA &);
    size_t length() const;
	RNA& trim(size_t );
	unordered_map<Nucl,int,hash<int>> cardinality() const;
	void print();
};
