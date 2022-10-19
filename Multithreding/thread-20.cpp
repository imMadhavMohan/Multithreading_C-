#include<iostream>
#include<thread>
#include<future>
#include<cmath>

// 1-1/3+1/5-1/7+1/9+.... = pi / 4 

using namespace std;

double findPi(double num){
    double sum = 0.0;

    for(int i=0;i<num;i++){
        double term = 1.0/(2*i+1);
        int sign = pow(-1,i);
        sum+=(sign*term);
    }
    return sum*4;
}

int main(){
    promise<double> prom;   

    auto do_calc = [&](int num){
        auto res = findPi(num);        
        prom.set_value(res);
    };

    thread t1(do_calc, 1E8);

    future<double> my_res = prom.get_future();

    cout<<my_res.get();

    t1.join();
    return 0;
}