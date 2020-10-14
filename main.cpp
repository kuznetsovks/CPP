#include <iostream>
#include <cmath>
#include "rna.h"
using namespace std;

int main()
{
    RNA  a(U,19);
    RNA  b(U,19);
    b[18]=a[18];
    bool g=b!=a;
    bool h=b==a;
    cout<<h<<endl;
    cout<<b.contsize<<endl;
    cout<<b.capacity<<endl;
    for (size_t i = 0; i < ceil(19/16.0); i++) {
    cout << bitset<sizeof(b.cont[i])* CHAR_BIT>(b.cont[i]) << endl;
	}
    //for (size_t i = 0; i < ceil(16/16.0); i++) {
    //cout << bitset<sizeof(a.cont[i])* CHAR_BIT>(a.cont[i]) << endl;
	//}

    cout << "Hello world!" << endl;
    return 0;
}
