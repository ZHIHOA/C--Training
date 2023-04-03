#!/usr/bin/python
# -*- coding: utf-8 -*-

import xml.etree.ElementTree as ET
import numpy as np


def load_opendrive(file_path):
    # 解析OpenDRIVE文件
    tree = ET.parse(file_path)
    root = tree.getroot()
    
# 遍历所有道路
    for road in root.findall('./road'):
        road_id = road.get('id')
        road_name = road.get('name')
        road_length = float(road.get('length'))
        # 遍历所有几何形状
        for geometry in road.findall('./planView/geometry'):
            geometry_s = float(geometry.get('s'))
            geometry_x = float(geometry.get('x'))
            geometry_y = float(geometry.get('y'))
            geometry_hdg = float(geometry.get('hdg'))
            geometry_length = float(geometry.get('length'))
            # 如果几何形状是一条直线
            if geometry.find('./line') is not None:
                # 计算起点和终点
                start_point = np.array([geometry_x, geometry_y])
                end_point = start_point + geometry_length * np.array([np.cos(geometry_hdg), np.sin(geometry_hdg)])
                # 生成参考线点
                ref_points = [start_point, end_point]
                # 连接相邻道路
                # TODO
                # 优化参考线
                # TODO
                # 导出参考线
                # TODO
        print(road_id)

if __name__=='__main__':
    file = "./ringroad.xodr"
    load_opendrive(file)