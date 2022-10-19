#include<iostream>
#include<thread>
#include<future>
#include<algorithm>
#include<cmath>

using namespace std;

typedef int long ul;

ul findOddSum(ul s, ul e){
    ul oddSum = 0;
    cout<<"id-2: "<<this_thread::get_id();

    cout<<'\n';
    for(ul i=s;i<e;i++){
        if(i&1)
            oddSum+=i;
    }

    return oddSum; // it's different from the promise as here val is returning
}

int main(){
    ul s = 0, e = 1900000000;
    cout<<"Thread created by below stmnt: ";

    future<ul> oddSum = async(launch::async, findOddSum, s, e); 
    // as compiler hits the above stmnt the parrellel execution becomes starts.
    cout<<"\n";

    cout<<"id-1: "<<this_thread::get_id();
    cout<<"\nWaiting for result:\n";
    cout<<oddSum.get();

    return 0;
}

