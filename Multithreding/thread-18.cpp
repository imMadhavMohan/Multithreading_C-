#include <iostream>
#include <iomanip>
#include <cmath>

// 1-1/3+1/5-1/7+1/9+.... = pi / 4 

using namespace std;

double CalculatePi(double num){
    double sum = 0.0;
    for(int i=0;i<num;i++)
    {
        double term = 1.0/(2*i+1);
        int sign = pow(-1,i);
        sum += (sign*term);
    }
    return (sum*4); // we want pi = 3.14
}

int main(){
    cout<<"Pi: "<<setprecision(15)<<CalculatePi(1E6);
    return 0;
}