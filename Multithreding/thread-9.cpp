#include <iostream>
#include <string>
#include <thread>

using namespace std;

int main()
{
    string name = "Mukund\n";

    thread t1( [&name](){
        for(int i=0;i<4;i++)
            cout<<"User "<<i<<" ";         
        cout<<endl<<name; 
        this_thread::sleep_for(chrono::seconds(5));
    });

    cout << "\nName is: " << name << endl;
    cout<< "Num of threads: "<<thread::hardware_concurrency()<<endl;
    if (t1.joinable())
        t1.join();
    cout << "\nName is: " << name;
    return 0;
}