#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

template<typename T>
bool close_enough(T a, T b)
{
 return a == b;
}
template <>
bool close_enough<double>(double a,double b)
{
 return abs(a - b)<0.01;
}

int main()
{
    assert(close_enough(1.0,1.0)==1);

    cout<<close_enough(1.0,1.0)<<endl;

    return 0;
}


