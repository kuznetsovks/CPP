#include <iostream>
#include <cassert>
using namespace std;

template<class A,class B>
auto multiply_functions(A f1,B f2)
{
    auto f3 = f1*f2;
return f3;
}
double f1(double x,double y){
    return x+y;
}
double f2(double x,double y){
    return x/y;
}
int main()
{
    assert(multiply_functions(f1(1,1),f2(1,1))==2.);

   cout<<multiply_functions(f1(1,3),f2(1,3))<<endl;

    return 0;
}
