#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

// Solution Race around condition

using namespace std;

int main(){
    int cnt{0};
    mutex mtx;

    auto fun = [&](){
        for(int i=0;i<1000;i++)
        {
            mtx.lock();
            ++cnt;  // critical section
            mtx.unlock();
        }
    };

    thread t1(fun);

    thread t2(fun);

    t1.join();        
    t2.join();
    
    cout<<cnt<<endl;

    return 0;
}

