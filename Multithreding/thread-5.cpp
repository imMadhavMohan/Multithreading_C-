#include <iostream>
#include <thread>

// Joinable()

using namespace std;

void sayHi(string name){
    cout<<"Hi "<<name<<endl;
}

void sayBye(string name){
    cout<<"Bye "<<name<<endl;
}

int main(){
    thread t1(sayHi,"Madhav");
    if(t1.joinable()){
        thread t2(sayBye,"Madhav");
        if(t2.joinable())
            t2.join();
    }    
    t1.join();
    return 0;    
}