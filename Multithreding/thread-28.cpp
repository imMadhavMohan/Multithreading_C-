#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

deque<int> deq;
const int max_size = 50;

condition_variable cv;
mutex mtx;

void consumer()
{
    while (true)
    {
        unique_lock<mutex> ul(mtx);
        cv.wait(ul, [&]
            { return deq.size() > 0; });
        int val = deq.back();
        deq.pop_back();
        cout << "Consumed " << val << endl;
        ul.unlock();
        cv.notify_one();
    }
}

void producer(int val)
{
    while (val)
    {
        unique_lock<mutex> ul(mtx);
        cv.wait(ul, [&]
            { return deq.size() < max_size; });
        deq.push_back(val);
        cout << "Produced " << val << endl;
        val--;
        ul.unlock();
        cv.notify_one();
    }
}

int main()
{
    thread t1(&producer, 100);
    thread t2(&consumer);

    t2.join();
    t1.join();
    cout << thread::hardware_concurrency() << endl; // ret num of concurrent thread supported by sysytem
    return 0;
}