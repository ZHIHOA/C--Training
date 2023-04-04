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
    double s_offset; // ��������s����
    vector<Point> center_points; // �����������ϵĵ�
};

struct Road {
    vector<Lane> lanes; // ��·�ϵĳ���
};

struct ReferenceLine {
    vector<Point> reference_points; // �ο����ϵĵ�
};

// ����������֮��ľ���
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// ���ݵ�·��Ϣ����ο���
ReferenceLine calculate_reference_line(const Road& road, double lane_width) {
    ReferenceLine ref_line;
    // �ҵ���·������ߵĳ�����������
    const vector<Point>& left_lane_center_points = road.lanes.front().center_points;
    // ��ͷ��ʼ����������
    Point prev_ref_point = left_lane_center_points.front();
    for (const Point& center_point : left_lane_center_points) {
        double dist = distance(prev_ref_point, center_point);
        // ������볬���˳�����ȣ��ͽ���ǰ���ĵ�����ƽ�Ƴ������/2�ľ���õ��ο����ϵĵ�
        if (dist > lane_width) {
            double theta = atan2(center_point.y - prev_ref_point.y, center_point.x - prev_ref_point.x);
            double dx = lane_width / 2*cos(theta/M_PI) ;
            double dy = lane_width / 2*sin(theta/M_PI) ;
            Point ref_point = {prev_ref_point.x + dx, prev_ref_point.y + dy};
            ref_line.reference_points.push_back(ref_point);
            prev_ref_point = ref_point;
        }
    }
    // ������һ�����ĵ�����ƽ�Ƴ������/2�õ��Ĳο����ϵĵ�
    double theta = atan2(prev_ref_point.y - left_lane_center_points.back().y,
                         prev_ref_point.x - left_lane_center_points.back().x);
    double dx = lane_width / 2*cos(theta/M_PI);
    double dy = lane_width / 2*sin(theta/M_PI);
    Point ref_point = {prev_ref_point.x + dx, prev_ref_point.y + dy};
    ref_line.reference_points.push_back(ref_point);
    return ref_line;
}

int main() {
    // ��·��Ϣ
    Road road;
    road.lanes.resize(4);
    road.lanes[0].center_points = {{0, 0}, {0, 10}, {0, 20},{0, 30}};
    // cout<<road.lanes[1]<<endl;
    road.lanes[1].center_points = {{1, 0}, {1, 10}, {1, 20},{1, 30}};
    road.lanes[2].center_points = {{2, 0}, {2, 10}, {2, 20},{2, 30}};
   
    // �������
    double lane_width = 3.5;
    // ����ο���
    ReferenceLine ref_line = calculate_reference_line(road, lane_width);
    // ����ο����ϵĵ�
    for (const Point& ref_point : ref_line.reference_points) {
    cout << "(" << ref_point.x << ", " << ref_point.y << ")" << endl;
}
}