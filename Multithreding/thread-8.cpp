#include <iostream>
#include <string>
#include <thread>

using namespace std;

void sayHi(string name){
    for(int i=0;i<4;i++){
        cout<<"User "<<i<<" ";
    }
    cout<<endl<<name;
}

int main(){
    string name = "Mukund\n";
    thread t1(sayHi,move(name));
    cout<<"\nName is: "<<name<<endl;
    if(t1.joinable())
        t1.join();
    cout<<"\nName is: "<<name;        
    return 0;
}