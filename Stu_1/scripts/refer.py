import numpy as np
from opendrivepy.opendriveparser import OpenDriveParser


def load_opendrive_map(filename):
    """读取opendrive地图文件"""
    parser = OpenDriveParser(filename)
    return parser.opendrive_dict


def calculate_reference_line(centerline, lane_width, lane_count):
    """根据道路中心线和车道宽度计算车道中心线"""
    # 将中心线向左和向右移动，得到车道中心线
    left_shift = lane_width / 2
    right_shift = -lane_width / 2
    reference_lines = []
    for i in range(lane_count):
        shift = i * (left_shift + right_shift)
        reference_line = centerline + np.array([shift, 0])
        reference_lines.append(reference_line)
    return reference_lines


def generate_reference_line(opendrive_map):
    """生成参考线"""
    # 从opendrive地图中提取道路信息
    road_network = opendrive_map['road_network']
    # 遍历每一条道路
    for road_id, road in road_network.items():
        # 遍历每一个车道
        for lane_id, lane in road['lanes'].items():
            # 获取道路中心线
            centerline = lane['central_path']
            # 获取车道宽度
            lane_width = lane['width']
            # 获取车道数量
            lane_count = lane['count']
            # 根据道路中心线和车道宽度计算车道中心线
            reference_lines = calculate_reference_line(centerline, lane_width, lane_count)
            # 可以将参考线存储到文件中或者进行后续处理
            # 这里只是简单的打印出来
            for ref_line in reference_lines:
                print(f'Reference line for {road_id} {lane_id}: {ref_line}')
    