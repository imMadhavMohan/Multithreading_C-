#include<iostream>
#include<thread>
#include<future>

using namespace std;

void mul(promise<int>&& prom, int a,int b){
    prom.set_value(a*b);
}

int main(){
    promise<int> prom;
    future<int> my_res = prom.get_future();
    int a = 10,b = 5;

    thread t1(&mul,move(prom),a,b); // move share val as rvalue

    cout<<my_res.get();

    if(t1.joinable())
        t1.join();


    return 0;
}