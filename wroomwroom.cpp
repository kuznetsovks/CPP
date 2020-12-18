// wroomwroom.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mute;
condition_variable cv;
bool state = true;

class car {

public:

    static void drier() {
        for (int i=0;i<10;i++){
            unique_lock<mutex> lock(mute);
            cv.wait(lock, []() {return state == 0; });
            cout << this_thread::get_id() << " car is getting dried" << endl;
            auto int_ms = chrono::milliseconds(1);
            this_thread::sleep_for(int_ms);
            state = 1;
            cv.notify_one();
        }
    }

    static void painter() {
        for (int i = 0; i < 10; i++) {
            unique_lock<mutex> lock(mute);
            cv.wait(lock,[]() {return state==1;});
            cout << this_thread::get_id() << " car is getting painted" << endl;
            auto int_ms = chrono::milliseconds(1);
            this_thread::sleep_for(int_ms);
            state = 0;
            cv.notify_one();
        }
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
