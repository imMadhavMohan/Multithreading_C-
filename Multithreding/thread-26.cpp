#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;

mutex mtx;

long balance = 0;

condition_variable cv;

void addMoney(int money){
    lock_guard<mutex> lg(mtx);
    balance+=money;
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout<<"Money Added & current balance is: "<<balance;
    cout<<endl;
    cv.notify_one();
}

void withdrawMoney(int money){
    unique_lock<mutex> ul(mtx);
    cv.wait(ul,[]{return (balance!=0) ? true:false;});
    if(balance>=money){
        balance-=money;
        cout<<"Amount deducted: "<<money<<endl;
    }
    else{
        cout<<"Amount can't be deducted less amount"<<endl;
    }
    cout<<"Current balance: "<<balance<<endl;
}

int main(){    
    thread t2(withdrawMoney, 500);
    thread t1(addMoney, 600);

    t1.join();
    t2.join();

    return 0;
}
