#include <iostream>
#include <iomanip>
#include <cmath>
#include <thread>
#include <future>
#include <exception>

// 1-1/3+1/5-1/7+1/9+.... = pi / 4 

using namespace std;

double CalculatePi(double num){
    double sum = 0.0;

    if(num<1)
      throw runtime_error("Can't be less than 1")  ;

    for(int i=0;i<num;i++)
    {
        double term = 1.0/(2*i+1);
        int sign = pow(-1,i);
        sum += (sign*term);
    }
    return (sum*4); // we want pi = 3.14
}

int main(){
    // runs the fun asynchronously 
    packaged_task<double(int)> task(CalculatePi); // ret(double , arg (int))
    future<double> my_res = task.get_future();

    thread t1(move(task),1E6); 
    try{
        cout<<setprecision(15)<<my_res.get();
    }
    catch(const exception &e){
        cout<<"Hi! "<<e.what();
    }
    
    t1.join();
    // cout<<"Pi: "<<setprecision(15)<<CalculatePi(1E6);
    return 0;
}