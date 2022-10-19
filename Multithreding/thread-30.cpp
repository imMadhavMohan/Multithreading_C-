#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <future>
#include <chrono>
#include <cmath>
#include <condition_variable>

// Create threads pool

using namespace std;

condition_variable cv;
mutex mtx;

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

int work(int id){

    unique_lock<mutex> ul(mtx);   
    cout<<"Statrting thread->"<<id<<endl;     
    ul.unlock();

    int secondes = (5.0*rand()/RAND_MAX)+3;
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    return id;
}

int main(){
    BlockingQueue<shared_future<int>> futures(2); // future isn't copyble but shared_future<int> are

    thread t([&](){
        for(int i=1;i<6;i++){
            shared_future<int> f = async(launch::async, work, i);
            futures.push(f);
        }
      }
    );

    cout<<endl;

    for(int i=1;i<6;i++){
        shared_future<int> f = futures.front();
        int val = f.get();
        futures.pop();
        cout<<"Returns-> "<<val;
    }

    cout<<thread::hardware_concurrency();
    t.join();
    return 0;
}