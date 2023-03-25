#include<iostream>
#include"calable.h"

using namespace std;

int main()
{
    Cala::Cala_na::Calable ca;
    ca.fun();
    
    Cala::Calz::Compute compute;
    double ret = compute.sum(3,4);
    cout<<ret<<endl;
    return 0;

};
