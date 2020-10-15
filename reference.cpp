#include "reference.h"
#include "rna.h"
#include <iostream>
#include <cmath>
using namespace std;
    Reference::Reference(RNA* rna,size_t ind)
    {
        rind=ind;
        rrna=rna;
    }
    Reference& Reference::operator=(Nucl nucl)
    {
    size_t shift=2*(cross-1-(rind)%cross);
    rrna->cont[rind/cross] = rrna->cont[rind/cross] | (3<<shift);
    rrna->cont[rind/cross] = rrna->cont[rind/cross] ^ (3<<shift);
    rrna->cont[rind/cross] =(rrna->cont[rind/cross] | (nucl<<shift));
        return *this;
    }
    Reference& Reference::operator=(const Reference r)
    {

    size_t shift=2*(cross-1-(rind)%cross);
    size_t n1= r.rrna->cont[r.rind/cross]>>2*(cross-1-(rind)%cross)&3;

    rrna->cont[rind/cross] = rrna->cont[rind/cross] | (3<<shift);
    rrna->cont[rind/cross] = rrna->cont[rind/cross] ^ (3<<shift);
    rrna->cont[rind/cross] =(rrna->cont[rind/cross] | (n1<<shift));


    return *this;
    }
