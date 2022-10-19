#include <iostream>
#include <thread>
using namespace std;

void sayHi(string &name){
    name = "Mukund";
    cout<<name;
}

int main(){
    string name = "Madhav";
    thread t1(sayHi,ref(name));
    thread t2 = move(t1);
    if(t2.joinable())
        t2.join();
    // t1.join(); will give error as no more in existence whole job
    // hob transferred to t2
    cout<<endl<<name;
    return 0;
}

