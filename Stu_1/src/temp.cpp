#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Lane {
    vector<int> center_points; // �����������ϵĵ�
};

int main(){
    Lane l1;
    for(int i = 0;i<4;++i){
        l1.center_points.push_back(i);
    }

    cout<<l1.center_points[3]<<endl;
    

}