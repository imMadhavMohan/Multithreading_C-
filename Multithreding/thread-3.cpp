#include <iostream>
#include <thread>

using namespace std;

class Display{
    public:
        int n;
        Display():n(6){};
        void operator()(){ // Overloading ()
            for(int i=0;i<n;i++)
                cout<<"User-> "<<i<<endl;
        }
};

int main(){ // main prog is also a thread that's wait for the
    thread t1((Display())); // completion of the t1 thread before termination
    t1.join();
    return 0;
}