#include <iostream>
#include <cassert>
using namespace std;

template<class OP,typename ...Args>
int sum(OP f, Args... args) {

    return f(args...);

}

/*template<typename ...Args>
auto lamd = [](Args... x) {
    return (x + ...) ;
};*/


auto pluso = [] (int first, int second)
{

    return first + second;
};
auto minuso = [] (int first, int second)
{
    return first - second;
};
auto multiplyo = [] (int first, int second)
{
    return first * second;
};
int main()
{
      assert(sum(pluso,1,2)==3);
      assert(sum(minuso,1,2)==-1);
      assert(sum(multiplyo,1,2)==2);
    cout<<sum(pluso,1,2)<<endl;
    cout<<sum(minuso,1,2)<<endl;
    cout<<sum(multiplyo,1,2)<<endl;
    return 0;
}
