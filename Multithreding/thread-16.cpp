#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

// Solution Race around condition

using namespace std;

void Count(mutex &mtx, int &cnt){
    for(int i=0;i<1000;i++)
        {
            mtx.lock();
            ++cnt;  // critical section
            mtx.unlock();
        }
}

int main(){
    int cnt{0};   
    mutex mtx;

    thread t1(&Count, ref(mtx), ref(cnt));

    thread t2(&Count, ref(mtx), ref(cnt));

    t1.join();        
    t2.join();
    
    cout<<cnt<<endl;

    return 0;
}

