#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

void sayHi(string name){
    for(int i=0;i<5;i++)
        cout<<"User "<<i;
    cout<<"Hi "<<name;
    this_thread::sleep_for(chrono::seconds(5));
}

int main(){
    thread t1(sayHi, "Madhav");
    cout<<"Hi maddy my boy ";
    t1.detach(); // this thread completely breaked from its parent
    return 0;
}

