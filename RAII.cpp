// RAII.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

 class RAII {
 private:
     thread & th;
 public:
     explicit RAII(thread& t) :th(t)
     {
     }
     ~RAII() {
         if (th.joinable()) {
             th.join(); 
             cout <<  "RAII destriyed object and join" << endl;
         }
         cout << " Destruction completed" << endl;
     }

     RAII(const RAII&) = delete;

     RAII& operator=(const RAII&) = delete;
};




 class work {
 private:
     int num;
 public:
     work(int num) : num(num) {
     }

     work(work const& another) : num(another.num)
     {
     }

     work& operator=(work const& another)
     {
         num = another.num;
         return *this;
     }

     ~work() {

     }

     void operator() () {
         for (int i = 0; i < num; ++i) {
             cout << i << endl;
         }
     }


 };



int main()
{
    thread t(work(5));
    RAII g(t); 
    cout << "Begin " << endl;
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
