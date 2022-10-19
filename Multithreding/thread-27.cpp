#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// Blcking Queue | Producer Consumer

using namespace std;

template<typename T>
class BlockingQueue
{
private:
    mutex mtx;
    int max_size;
    queue<T> Q;
    condition_variable cv;
public:
    BlockingQueue(int max):max_size(max){};
    void push(T val)
    {
        unique_lock<mutex> ul(mtx);
        cv.wait(ul,[this](){return Q.size()<max_size;});
        Q.push(val);
        ul.unlock();
        cv.notify_one();
    }

    T front(){
        unique_lock<mutex> ul(mtx);
        cv.wait(ul, [this](){return !Q.empty();});
        ul.unlock();
        return Q.front();
    }

    void pop()
    {
        unique_lock<mutex> ul(mtx);
        cv.wait(ul,[this](){return !Q.empty();});        
        Q.pop();
        ul.unlock();
        cv.notify_one();        
    }

    T size(){
        return Q.size();
    }
};


int main(){
    BlockingQueue<int> Qu(5);
    
    thread t1([&](){
        for(int i=1;i<11;i++){
            cout<<"Push "<<i<<endl;
            cout<<"queue size "<<Qu.size()<<endl;
            Qu.push(i);
            cout<<endl;
        }
    });

    thread t2([&](){
        for(int i=1;i<11;i++){            
            auto item = Qu.front();
            Qu.pop();
            cout<<"consumed item "<<item<<endl;
        }
    });

    t1.join();
    t2.join();

    return 0;
}