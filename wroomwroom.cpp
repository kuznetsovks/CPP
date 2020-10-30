// wroomwroom.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;
condition_variable cv;
bool state = false;

class car {

public:
    static void drier() {
        unique_lock<mutex> lock(m);

        cout << this_thread::get_id() << " car is getting dried" << endl;
        cv.wait(lock);
        //painter();
        //state = 0;

        cv.notify_all();
    }
    static void painter() {
        unique_lock<mutex> lock(m);

        cout <<this_thread::get_id() << " car is getting painted" << endl;
        cv.wait(lock);
        //drier();
        cv.notify_all();
        //state = 1;

    }
};

int main() {
    car Bently;
    thread thr1(car::drier);
    thread thr2(car::painter);
    thr1.join();
    thr2.join();
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
