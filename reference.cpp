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
        //size_t shift=2*(cross-1-(rind)%cross);
       // size_t n= rrna->cont[1/cross]>>2*(cross-1-(rind)%cross)&3;
        //Nucl nucl=static_cast<Nucl>(n);
        //std::cout<<nucl<<std::endl;

        return *this;
    }
    Reference& Reference::operator=(const Reference r)
    {

    size_t shift=2*(cross-1-(rind)%cross);
    size_t n1= r.rrna->cont[r.rind/cross]>>2*(cross-1-(rind)%cross)&3;

    rrna->cont[rind/cross] = rrna->cont[rind/cross] | (3<<shift);
    rrna->cont[rind/cross] = rrna->cont[rind/cross] ^ (3<<shift);
    rrna->cont[rind/cross] =(rrna->cont[rind/cross] | (n1<<shift));


    //for (size_t i = 0; i < 1; i++) {
    //cout << bitset<sizeof(qwe.cont[i])* CHAR_BIT>(qwe.cont[i]) << endl;
	//}
    //for (size_t i = 0; i < 1; i++) {
    //std::cout << std::bitset<sizeof(rrna.cont[i])* CHAR_BIT>(cont[i]) << std::endl;
    //}
//    rrna->cont[1/cross]=n<<
    //rrna->operator[](rind).operator=(nucl1);
    return *this;
    }
