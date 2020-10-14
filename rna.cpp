
#include <utility>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cmath>
#include "rna.h"

using namespace std;

 size_t* RNA::createRNA(size_t n){
        blocks= ceil(1.0*n/cross);

        size_t *nArr = new size_t[blocks];

        for (size_t i = 0; i < blocks; i++)
            {
                nArr[i]=0;
            }
            return nArr;
    }
    RNA::RNA()
    {
        contsize = 1;
        capacity = cross;
        cont=createRNA(contsize);
    };
    RNA::RNA(Nucl Nu,size_t size)
    {
        contsize = size;
        capacity = ceil(1.0*contsize/cross)*cross;
        cont = createRNA(contsize);
        size_t j = 0;
        for (size_t i = 0; i < contsize; i++) {
            if (j == cross)
                j = 0;
            cont[i/cross] = cont[i/cross] | (Nu<<2*(cross-1-j));
            j++;
        }
    }
    RNA::~RNA()
    {
        delete[] cont;
    }
    RNA::RNA(const RNA& a)
    {
        if (a.cont==nullptr)
        {
            cont=nullptr;
        }
        else
        {
            blocks = a.blocks;
            contsize=a.contsize;
            capacity=a.capacity;
            cont = createRNA(contsize);
            memcpy(cont,a.cont,blocks*sizeof(size_t));

        }
    }


    size_t RNA::cardinality(Nucl value)
    {
        size_t count=0;
        size_t n,nt;
        size_t j=0;
        for (size_t i = 0; i < contsize; i++) {
            if (j==cross)
                j = 0;
            n= (cont[i/cross]>>2*(cross-1-j))&3;
            if (static_cast<Nucl>(n)==value)
                count++;
            j++;

        }
    return count;
    }

    RNA& RNA::operator=(const RNA& a)
    {
        if (this!=&a){
        if (a.cont==nullptr)
        {
            cont=nullptr;
        }
        else
        {
            blocks = a.blocks;
            contsize=a.contsize;
            capacity=a.capacity;
            cont = createRNA(contsize);
            memcpy(cont,a.cont,blocks*sizeof(size_t));

        }
        }
        return *this;
    }
    bool RNA::operator!=(const RNA& a)
    {
        if (contsize!=a.contsize)
            {
                return true;
            }
        size_t j = 0;
        size_t n1,n2;
        Nucl nucl1,nucl2;
        for (size_t i = 0; i < a.contsize; i++) {
            if (j == cross)
                j = 0;
            n1= a.cont[i/cross]>>2*(cross-1-j)&3;
            n2=this->cont[i/cross]>>2*(cross-1-j)&3;
            nucl1=static_cast<Nucl>(n1);
            nucl2=static_cast<Nucl>(n2);
            if (nucl2!=nucl1){
                return true;
            }
            j++;
        }
        return false;
    }
    bool RNA::operator==(const RNA& a)
    {
        if (contsize!=a.contsize)
            {
                return false;
            }
        size_t j = 0;
        size_t n1,n2;
        Nucl nucl1,nucl2;
        for (size_t i = 0; i < a.contsize; i++) {
            if (j == cross)
                j = 0;
            n1= a.cont[i/cross]>>2*(cross-1-j)&3;
            n2=this->cont[i/cross]>>2*(cross-1-j)&3;
            nucl1=static_cast<Nucl>(n1);
            nucl2=static_cast<Nucl>(n2);
            if (nucl2!=nucl1){
                return false;
            }
            j++;
        }
        return true;
    }
   Reference RNA::operator[](size_t ind)
    {
        if ((ind>=contsize) or (ind<0))
            {
                throw out_of_range("bad index");
            }
            else
            {
                Reference a(this,ind);
                return a;
            }
    }

