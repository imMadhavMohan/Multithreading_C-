#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <future>
#include <chrono>
#include <condition_variable>

// Create multiple threads

using namespace std;

condition_variable cv;
mutex mtx;

int work(int id){

    unique_lock<mutex> ul(mtx);   
    cout<<"Statrting thread->"<<id<<endl;     
    ul.unlock();

    this_thread::sleep_for(chrono::milliseconds(2000));
    
    return id;
}

int main(){
    vector<shared_future<int>> futures; // future isn't copyble but shared_future<int> are

    for(int i=1;i<6;i++){
        shared_future<int> f = async(launch::async, work, i);
        futures.push_back(f);
    }
    cout<<endl;
    for(auto i:futures){
        cout<<"Returns-> "<<i.get()<<endl;
    }

    cout<<thread::hardware_concurrency();

    return 0;
}