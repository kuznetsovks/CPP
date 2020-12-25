#include <iostream>
#include <cmath>
#include "dna.h"
#include <ctime>
using namespace std;

int main()
{
    RNA  a(G,10);
    a.print();
    a.push_back(A);
    a.print();
    

    //
    //a[17] = U;
    //a.print();
    /*
    RNA  b(C,16);

    cout<<"Constuctor"<<endl;
    a.print();
    cout<<endl;

    cout<<"Operator []"<<endl;
    a[1]=C;
    a.print();
    a[1]=b[14];
    a.print();


    //for (size_t i=a.length();i<1000000;i++)
    //{
     //   a[i] = C;
   // }
    //a[1000]=C;
    //a.print();
    cout<<endl;

    cout<<"Operator ="<<endl;
    a=b;
    a.print();
    cout<<endl;

    cout<<"Cardinality"<<endl;
    cout<<a.cardinality(C)<<endl;
	unordered_map<Nucl,int,hash<int>> map = a.cardinality();
    for( auto x:map)
        {
        cout<<x.first<<" - "<<x.second<<endl;
        }
    cout<<endl;

    cout<<"Complementary"<<endl;
    RNA  c(G,16);
    RNA  d(C,16);
    c.print();
    d.print();
    cout<<"true or false:"<<c.isComplementary(d)<<endl;
    cout<<endl;

    cout<<"DNA"<<endl;
    DNA jj(d,c);
    jj.print();
    cout<<endl;

    cout<<"trim"<<endl;
    a.trim(5);
    a.print();
    cout<<endl;

    cout<<"split"<<endl;
    c.split(5,1);
    c.print();
    cout<<endl;

    cout<<"operator +"<<endl;
    RNA e=c+a;
    e.print();
    cout<<endl;

    cout<<"length"<<endl;
    cout<<e.length()<<endl;
    cout<<endl;

    cout<<"operator =="<<endl;
    bool yon=a==b;
    a.print();
    b.print();
    cout<<yon<<endl;
    cout<<endl;

    cout<<"operator !="<<endl;
    yon=a!=b;
    a.print();
    b.print();
    cout<<yon<<endl;
    cout<<endl;

    cout<<"operator !"<<endl;
    a.print();
    !a;
    a.print();
    cout<<endl;
    return 0;
    */
}
