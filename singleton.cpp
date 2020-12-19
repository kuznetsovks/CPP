// singleton.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton_
{
private:
    Singleton_(const string value) : val(value)
    {
    }
    ~Singleton_()
    {
    }


    Singleton_(const Singleton_& signal);
    const Singleton_& operator=(const Singleton_& signal);

    //static Singleton_* m_Singleton_;
    static atomic<Singleton_*> m_Singleton_;
    static mutex m_Mutex;
    string val;
public:
    static Singleton_*& GetInstance(const string& value)
    {
        Singleton_* p = m_Singleton_.load(memory_order_acquire);
        if (p == NULL)
        {
            unique_lock<mutex> lock(m_Mutex); 
            p = m_Singleton_.load(memory_order_relaxed);
            if (p == NULL)
            {
                p = new  Singleton_(value); //(nothrow)
                m_Singleton_.store(p, memory_order_release);
            }
        }

        return p;
    }
    
    static void deleteInstance()
    {
        unique_lock<mutex> lock(m_Mutex); 
        if (m_Singleton_)
        {
            delete m_Singleton_;
            m_Singleton_ = NULL;
        }
    }

    void Print() {
        cout << "memory address:" << this << endl;
    }
    string value() const {
        return val;
    }


};

//SingleInstance* SingleInstance::m_SingleInstance = NULL;
atomic<Singleton_*> Singleton_::m_Singleton_ =NULL;
mutex Singleton_::m_Mutex;


void ThreadFoo() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton_* singleton = Singleton_::GetInstance("FOO");
    cout << singleton->value() << endl;
}

void ThreadBar() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton_* singleton = Singleton_::GetInstance("BAR");
    cout << singleton->value() << endl;
}

int main()
{
    thread t1(ThreadFoo);
    thread t2(ThreadBar);
    t1.join();
    t2.join();
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
