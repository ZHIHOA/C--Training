#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int> vec0;
    for (int i = 0; i < 10; i++)
    {
        /* code */
        vec0.push_back(i);
    }
    
    cout<<"vec0 status:"<<vec0.size()<<endl;
    vector<int>::iterator it;
    for (auto it = vec0.begin(); it !=vec0.end(); ++it)
    {
        /* code */
        cout<<*it<<endl;
        *it*=2;
    }
    cout<<"--------------------------------"<<endl;
    for (vector<int>::reverse_iterator it2 =vec0.rbegin(); it2 != vec0.rend(); ++it2)
    {
        /* code */
        cout<<*it2<<endl;
        

    }
    
    
    


    // int i=10;
    // int *p;
    // p=&i;
    // cout<<p<<*p<<endl;


    
}