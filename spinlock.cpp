// spinlock.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <atomic>
#include <thread>

using namespace std;

class spinlock_ {
    atomic_flag lock_flag;
public:
    spinlock_() {
        lock_flag.clear(); 
    }

    bool try_lock() {
        return !lock_flag.test_and_set(memory_order_acquire); 
    }
    void lock() { 
        for (size_t i = 0; !try_lock(); ++i) 
            if (i % 100 == 0) 
                this_thread::yield(); 
    }
    void unlock() {
        lock_flag.clear(memory_order_release); 
    }
};

int common_var = 0;
spinlock_ spinlock;

void add_to_shared() {
    spinlock.lock();
    common_var = common_var+1;
    spinlock.unlock();
}

int main() {

    thread t1([&]() { add_to_shared(); });
    thread t2([&]() { add_to_shared(); });
    t1.join(); t2.join();
    cout << "shared_value = " << common_var<< endl;;
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
