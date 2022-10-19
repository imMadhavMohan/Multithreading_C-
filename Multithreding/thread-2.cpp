#include <iostream>
#include <thread>
using namespace std;

auto cntSum = [](int &sum, int n,  int* arr) {
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }        
};

int main(){    
    int n=6, sum=0;
    int arr[6] = {1,2,3,4,5,6};
    thread t1(cntSum, ref(sum), n, arr);
    t1.join();
    cout<<"Sum is: "<<sum;
    return 0;
}