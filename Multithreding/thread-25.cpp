#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;
// wait for a thread

int main(){
    bool ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        ready = true;
    });

    while(!ready){
        this_thread::sleep_for(chrono::milliseconds(3000));
        cout<<"I got chance";
    }

    t1.join();
    return 0;
}