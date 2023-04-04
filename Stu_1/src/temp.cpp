#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Lane {
    vector<int> center_points; // 车道中心线上的点
};

int main(){
    Lane l1;
    for(int i = 0;i<4;++i){
        l1.center_points.push_back(i);
    }

    cout<<l1.center_points[3]<<endl;
    

}