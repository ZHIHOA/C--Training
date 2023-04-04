#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

struct Point {
    double x;
    double y;
};

struct Lane {
    double s_offset; // 车道起点的s坐标
    vector<Point> center_points; // 车道中心线上的点
};

struct Road {
    vector<Lane> lanes; // 道路上的车道
};

struct ReferenceLine {
    vector<Point> reference_points; // 参考线上的点
};

// 计算两个点之间的距离
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// 根据道路信息计算参考线
ReferenceLine calculate_reference_line(const Road& road, double lane_width) {
    ReferenceLine ref_line;
    // 找到道路上最左边的车道的中心线
    const vector<Point>& left_lane_center_points = road.lanes.front().center_points;
    // 从头开始遍历中心线
    Point prev_ref_point = left_lane_center_points.front();
    for (const Point& center_point : left_lane_center_points) {
        double dist = distance(prev_ref_point, center_point);
        // 如果距离超过了车道宽度，就将当前中心点向左平移车道宽度/2的距离得到参考线上的点
        if (dist > lane_width) {
            double theta = atan2(center_point.y - prev_ref_point.y, center_point.x - prev_ref_point.x);
            double dx = lane_width / 2*cos(theta/M_PI) ;
            double dy = lane_width / 2*sin(theta/M_PI) ;
            Point ref_point = {prev_ref_point.x + dx, prev_ref_point.y + dy};
            ref_line.reference_points.push_back(ref_point);
            prev_ref_point = ref_point;
        }
    }
    // 添加最后一个中心点向左平移车道宽度/2得到的参考线上的点
    double theta = atan2(prev_ref_point.y - left_lane_center_points.back().y,
                         prev_ref_point.x - left_lane_center_points.back().x);
    double dx = lane_width / 2*cos(theta/M_PI);
    double dy = lane_width / 2*sin(theta/M_PI);
    Point ref_point = {prev_ref_point.x + dx, prev_ref_point.y + dy};
    ref_line.reference_points.push_back(ref_point);
    return ref_line;
}

int main() {
    // 道路信息
    Road road;
    road.lanes.resize(4);
    road.lanes[0].center_points = {{0, 0}, {0, 10}, {0, 20},{0, 30}};
    // cout<<road.lanes[1]<<endl;
    road.lanes[1].center_points = {{1, 0}, {1, 10}, {1, 20},{1, 30}};
    road.lanes[2].center_points = {{2, 0}, {2, 10}, {2, 20},{2, 30}};
   
    // 车道宽度
    double lane_width = 3.5;
    // 计算参考线
    ReferenceLine ref_line = calculate_reference_line(road, lane_width);
    // 输出参考线上的点
    for (const Point& ref_point : ref_line.reference_points) {
    cout << "(" << ref_point.x << ", " << ref_point.y << ")" << endl;
}
}