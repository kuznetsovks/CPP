#include <iostream>
#include <cassert>
using namespace std;
template<typename T>
auto suml(T t) {
    return t;
}
template <class T, class ...Args>
auto suml(T value, Args... args) {
    return value + suml(args...);
}

template<typename ...Args>
int sum(Args... args) {

    return (args + ...);

}
int main()
{
    cout<<suml(1,2,3);
    cout<<sum(1,2,3);

    return 0;
}


