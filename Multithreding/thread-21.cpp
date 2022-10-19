#include<iostream>
#include<thread>
#include<future>
#include<cmath>
#include <iomanip>
#include<exception>

// 1-1/3+1/5-1/7+1/9+.... = pi / 4 

using namespace std;

double findPi(double num){
    if(num<1)
        throw runtime_error("num can't be less than one");

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
        try
        {
            auto res = findPi(num);        
            prom.set_value(res);
        }
        catch(...)
        {
            prom.set_exception(current_exception());
        }
                
    };

    thread t1(do_calc, 0);
    
    future<double> my_res = prom.get_future();

    try
    {
        cout<<setprecision(15)<<my_res.get();
    }
    catch(const std::exception& e)
    {
        cerr <<"hey "<< e.what() << '\n';
    }
    
  
    t1.join();
    return 0;
}