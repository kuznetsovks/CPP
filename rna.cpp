#include <iostream>
#include <cmath>
#include <cassert>
#include <bitset>
#include <unordered_map>
using namespace std;
enum Nucl
{
    A, G, C, U
};

class RNA
{

public:
    size_t cross=sizeof(size_t)/2*8;
    size_t contsize;
    size_t capacity;
    size_t* cont;
    size_t* createRNA(size_t n){
        size_t nsize= ceil(1.0*n/cross);

        size_t *nArr = new size_t[nsize];

        for (size_t i = 0; i < nsize; i++)
            {
                nArr[i]=0;
            }
            return nArr;
    }
    RNA()
    {
        contsize = 1;
        capacity = cross;
        cont=createRNA(contsize);
    };
    RNA(Nucl Nu,size_t size)
    {
        contsize = size;
        capacity = ceil(1.0*contsize/cross)*cross;
        cont=createRNA(contsize);
        size_t j=0;
        for (size_t i = 0; i < contsize; i++) {
            if (j==cross)
                j = 0;
            cont[i/cross] = cont[i/cross] | (Nu<<2*(cross-1-j));
            j++;
        }
    }
    ~RNA()
    {
        delete[] cont;
    }

    size_t cardinality(Nucl value)
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



class Reference
{
public:
    size_t rind;
    RNA* rrna;
    Reference(){}
    Reference(RNA* rna,size_t ind)
    {
        rind=ind;
        rrna=rna;
    }
    ~Reference(){}

};
    Reference operator[](size_t ind)
    {
        if ((ind>contsize) or (ind<0))
            {
                throw out_of_range("bad index");
            }
            else
            {
                return Reference(this,ind);
            }
    }
friend RNA operator+(const RNA &rna1,const RNA &rna2)
{
    size_t commonsize = rna1.contsize+rna2.contsize;
    size_t commoncapacity = ceil(1.0*commonsize/rna1.cross)*rna1.cross;
    size_t ncont;
    size_t *nArr = new size_t[commonsize];
    size_t j=0;
    size_t n;

    cout<<commonsize<<endl;
    cout<<commoncapacity<<endl;
}
};

int main()
{
    RNA  a(G,15);
    RNA  b(C,16);

    cout<<endl;
    for (size_t i = 0; i < ceil(16/16.0); i++) {
    cout << bitset<sizeof(b.cont[i])* CHAR_BIT>(b.cont[i]) << endl;
	}
	cout<<endl;
    a+b;

    return 0;
}


