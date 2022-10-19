#include <iostream>
#include <bits/stdc++.h>
#include <thread>
#include <mutex>

// Solution Race around condition

using namespace std;

class Wallet
{
    int mMoney;
public:
    mutex mtx;
    Wallet() :mMoney(0){}
    int getMoney() { return mMoney; }
    void addMoney(int money)
    {
       lock_guard<mutex> lg(mtx);
       for(int i = 0; i < money; ++i)
       {
          mMoney++;
       }       
    }
};

int testMultithreadedWallet()
{
   Wallet obj;
   vector<thread> threads;
   for(int i = 0; i < 5; ++i){
        threads.push_back(thread(&Wallet::addMoney, &obj, 1000));
   }
   for(int i = 0; i < threads.size() ; i++)
   {
       threads.at(i).join();
   }
   return obj.getMoney();
}

int main()
{
  int val = 0;
  for(int k = 0; k < 1000; k++)
  {     
     if((val = testMultithreadedWallet()) != 5000)
     {
       std::cout << "Error at count = "<<k<<" Money in Wallet = "<<val << std::endl;
     }
  }
  return 0;
}