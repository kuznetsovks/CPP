#include <iostream>
#include <cmath>
#include "rna.h"
using namespace std;

int main()
{
    RNA  a(G,19);
    RNA  b(U,19);
    //b[18]=a[18];
    bool g=b!=a;
    bool h=b==a;
    cout<<h<<endl;
    cout<<b.contsize<<endl;
    cout<<b.capacity<<endl;
    for (size_t i = 0; i < ceil(19/16.0); i++) {
    cout << bitset<sizeof(b.cont[i])* CHAR_BIT>(b.cont[i]) << endl;
	}
    RNA d(U,19);
    !b;

    bool y=b.isComplementary(a);
    cout<<"asd"<<y<<endl;
    for (size_t i = 0; i < ceil(19/16.0); i++) {
    cout << bitset<sizeof(b.cont[i])* CHAR_BIT>(b.cont[i]) << endl;
	}
    //for (size_t i = 0; i < ceil(16/16.0); i++) {
    //cout << bitset<sizeof(a.cont[i])* CHAR_BIT>(a.cont[i]) << endl;
	//}
    a.split(5,false);
    cout<<"contsize"<<a.contsize<<endl;
    cout<<"asd"<<endl;
    for (size_t i = 0; i < ceil(a.contsize/16.0); i++) {
    cout << bitset<sizeof(a.cont[i])* CHAR_BIT>(a.cont[i]) << endl;
	}
    cout<<ceil(1.0*b.contsize/16)<<endl;
    for(int i=0;i<5;i++)
    cout << i << endl;
    return 0;
}
