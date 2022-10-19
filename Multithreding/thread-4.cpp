#include <iostream>
#include <thread>

using namespace std;

void sayHi(string str){
    cout<<"Hi "<<str<<endl;
}

void sayBye(string str){
    cout<<"Bye "<<str<<endl;
}

int main(){ // main prog is also a thread that's wait for the
    thread t1(sayHi,"Mukund"), t2(sayBye,"Madhav"); // completion of the t1 thread before termination
    
    if(t1.get_id()!=t2.get_id()) // executed earlier than the thread exe
        cout<<"Both t1 & t2 are different\n";
    else 
        cout<<"Both t1 & t2 are same\n";

    t2.join();
    t1.join();
    return 0;
}