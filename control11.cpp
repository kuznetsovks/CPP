#include <iostream>
#include <memory>

using namespace std;
template<class B>
class weak_ptr1
{
public:
        B *ptr=nullptr;
        shared_ptr<B> shptr;
    weak_ptr1(){}
    weak_ptr1(B A)
    {
      B *ptr= new B(A);
    }
    ~weak_ptr1()
    {
        delete ptr;
    }
    void reset()
    {
        *ptr=nullptr;
    }
    bool expired()
    {
        if (*ptr==nullptr) return 1;
            else return 0;
    }
    lock()
    {
        //shptr=
        //cout<<shptr<<endl;
       // *ptr=nullptr;
    }

};
int main()
{
    int a=5;
    weak_ptr1<int> b(a);
    b.lock();
    return 0;
}


