#include <unordered_map>
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


    size_t RNA::cardinality(Nucl value) const
    {
        size_t count=0;
        size_t n;
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
    RNA& RNA::operator!()
    {
        for (size_t i = 0; i < ceil(1.0*this->contsize/cross); i++) {
            cont[i]=~this->cont[i];
        }
        return *this;
    }
    bool RNA::isComplementary(RNA& b) const
    {
        RNA a(*this);
        if (a.contsize!=b.contsize)
            {
                throw out_of_range("bad index");

            }
        else{
        for (size_t i = 0; i < ceil(1.0*a.contsize/a.cross); i++) {
            a.cont[i]=~a.cont[i];
            }


            size_t j=0;
            size_t n1,n2;
            Nucl nucl1,nucl2;
            for (size_t i = 0; i < a.contsize; i++) {
                if (j == a.cross)
                    j = 0;
                n1= a.cont[i/a.cross]>>2*(a.cross-1-j)&3;
                n2= b.cont[i/a.cross]>>2*(a.cross-1-j)&3;
                nucl1=static_cast<Nucl>(n1);
                nucl2=static_cast<Nucl>(n2);
                if (nucl2!=nucl1){
                    return false;
                    }
                j++;
            }

            return true;
        }
    }

    bool RNA::operator!=(const RNA& a) const
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
    bool RNA::operator==(const RNA& a) const
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

    void RNA::push_back(const Nucl& N) {
        if (contsize != capacity) 
        {
            cont[contsize / cross] = cont[contsize / cross] | (N << sizeof(size_t) * 8 - 2 * (contsize % cross) - 2);
            contsize++;
        }
        else {
            capacity = capacity * 2;
            size_t* tmp = createRNA(capacity);
            memcpy(tmp, cont, contsize * 2 / 8);
            delete[] cont;
            cont = tmp;
            tmp = nullptr;
            size_t ContainerIndex = contsize / cross;
            cont[ContainerIndex] = cont[ContainerIndex] | (N << sizeof(size_t) * 8 - 2);
            contsize++;
        } 
    }

   Reference RNA::operator[](size_t ind)
    {
        if ( (ind<0))
            {
                throw out_of_range("bad index");
            }
        else if ((ind>=contsize) & (ind>capacity))
        {
        RNA b(A,ind);

        size_t n1;
            memcpy(cont, b.cont, blocks * sizeof(size_t));
            n1=this->cont[blocks /this->cross]>>2*(this->cross-1-ind)&3;
            b.cont[blocks/this->cross]=b.cont[blocks/this->cross] | n1<<2*(this->cross-1-ind);
            //j++;
        //}
        *this=b;
        Reference bb(this,ind);
        return bb;
        }
        else if ((ind >= contsize) & (ind <= capacity))
        {
            size_t n1;
                n1 = this->cont[blocks / this->cross] >> 2 * (this->cross - 1 - ind) & 3;
                cont[blocks / this->cross] = cont[blocks / this->cross] | n1 << 2 * (this->cross - 1 - ind);
            Reference bb(this, ind);
            return bb;
        }
        else
        {
            Reference a(this,ind);
            return a;
        }

    }

    RNA& RNA::split(size_t ind,bool id)
    {
        if ((ind >=this->contsize) || (ind< 0))
            {
            throw out_of_range("Invalid index");
            }
        size_t len=this->contsize-ind;
        RNA a(A,ind), b(A,len);
        size_t n1;
        size_t j=0;
        for (size_t i = 0; i < ind; i++) {
            if (j == cross)
                j = 0;
            n1=this->cont[i/cross]>>2*(cross-1-j)&3;
            a.cont[i/cross]=a.cont[i/cross] | n1<<2*(cross-1-j);
            j++;
        }
        j=0;
        size_t jj=0;;
        for (size_t i = ind; i < this->contsize; i++) {
            if ((j == cross) )
                j = 0;
            if (j==cross-ind)
                {
                j=0;
            jj=cross-ind;
            }
            n1=this->cont[i/cross]>>2*(cross-1-j)&3;
            b.cont[(i-ind)/cross]=b.cont[(i-ind)/cross] | n1<<2*(cross-1-j-jj);
            j++;
        }
        if (id==true)
        *this=a;
        if (id==false)
        *this=b;
        return *this;
    }
    RNA operator+(const RNA & a,const RNA & b)
    {
        size_t commonsize= a.contsize+b.contsize;
        RNA c(A,commonsize);
        size_t j=0;
        size_t n1;
        for (size_t i = 0; i < a.contsize; i++) {
            if (j == a.cross)
                j = 0;
            n1=a.cont[i/a.cross]>>2*(a.cross-1-j)&3;
            c.cont[i/a.cross]=c.cont[i/a.cross] | n1<<2*(a.cross-1-j);
            j++;
        }

        size_t jj=j;
        j=0;
        for (size_t i = a.contsize; i < commonsize; i++) {
            if ((j == b.cross) )
                j = 0;
            if (j==b.cross-a.contsize)
                {
                //j=0;
            //jj=b.cross-a.contsize;
            }
            n1=b.cont[(i-a.contsize)/b.cross]>>2*(b.cross-1-j)&3;
           c.cont[(i)/b.cross]=c.cont[(i)/b.cross] | n1<<2*(b.cross-1-j-jj);
            j++;
        }
        return c;
    }
    size_t RNA::length() const {
        return this->contsize;
    }

    RNA& RNA::trim(size_t ind)
    {
        if ((ind >= this->contsize) || (ind < 0))
            {
            throw out_of_range("Invalid index");
            }
        RNA a(A,ind);
        size_t n1;
        size_t j=0;
        for (size_t i = 0; i < ind; i++) {
            if (j == cross)
                j = 0;
            n1=this->cont[i/cross]>>2*(cross-1-j)&3;
            a.cont[i/cross]=a.cont[i/cross] | n1<<2*(cross-1-j);
            j++;
        }
        j=0;

        *this=a;
        return *this;
    }

    unordered_map<Nucl, int, hash<int>> RNA::cardinality() const
    {
        unordered_map<Nucl, int, hash<int>> unomap;
            unomap[A]=this->cardinality(A);
            unomap[G]=this->cardinality(G);
            unomap[C]=this->cardinality(C);
            unomap[U]=this->cardinality(U);
        return unomap;
    }
    void RNA::print()
    {
    for (size_t i = 0; i < ceil(1.0*this->contsize/16.0); i++) {
    cout << bitset<sizeof(this->cont[i])* CHAR_BIT>(this->cont[i]) << endl;
	}
    }
