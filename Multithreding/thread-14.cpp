#include <iostream>
#include <thread>
#include <atomic>

// Solution Race around condition

using namespace std;

int main(){
    atomic<int> cnt{0};
    // atomic oper will ensure that every oper on on cnt will be atomic    

    thread t1([&cnt](){
        for(int i=0;i<1000;i++)
            ++cnt;
    });

    thread t2([&cnt](){
        for(int i=0;i<1000;i++)
            ++cnt;
    });

    t1.join();        
    t2.join();
    
    cout<<cnt;

    return 0;
}

