#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;

mutex mtx;

double CalculatePi(int num, int start, int skip)
{
    
    double sum = 0;

    for (int i = start; i < num; i+=skip)
    {
        double sign = pow(-1, i);
        double term = 1 / (2 * i + 1);
        sum += (term * sign);
    }
    
    return sum;
}

int main()
{
    vector<shared_future<double>> futures;
    int num = 12;

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < num; i++)
    {
        shared_future<double> f = async(launch::async, CalculatePi, 1E8, i, num);
        futures.push_back(f);
    }

    double sum = 0.0;

    for (auto f : futures)
    {
        sum += f.get();
    }
    auto end = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "duration: " << duration << endl;
    cout << setprecision(15) << "Sum: " << sum << endl;

    return 0;
}