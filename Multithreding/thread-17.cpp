#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

// Solution Race around condition
// Use lock_guard recommended over mutex as if mutex lock remained 
// locked so else wont able to acquire it

using namespace std;

void Count(mutex &mtx, int &cnt){    
    for(int i=0;i<1000;i++)
      {
         lock_guard<mutex> lg(mtx);
         ++cnt;  // critical section            
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

