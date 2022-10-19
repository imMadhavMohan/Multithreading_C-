#include <iostream>
#include <thread>
using namespace std;

void printNum(int &sum, int *arr, int n){
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
}

// whenever you passed the value by refernce always pass it
// using ref(val) to aviod error

int main() {    
    int sum{0},n=5;
    int arr[] = {1,2,3,4,5};
    thread t1(printNum, ref(sum), arr, n);
    t1.join(); 
    cout<<"Sum is: "<<sum;
    return 0;
}