import xml.etree.ElementTree as ET
import numpy as np
from scipy.interpolate import CubicSpline

# 解析OpenDRIVE文件
def parse_opendrive(file_path):
    tree = ET.parse(file_path)
    root = tree.getroot()

    # 获取道路和车道信息
    road = root.find('road')
    geometry = road.find('geometry')
    lane_section = road.find('lanes').find('laneSection')
    center_line = geometry.find('center').findall('line')

    # 获取道路宽度和车道数量
    road_width = float(geometry.find('width').text)
    lane_count = len(lane_section.findall('left')) + 1

    # 获取车道中心线
    center_x = []
    center_y = []
    for line in center_line:
        for point in line.findall('point'):
            x = float(point.attrib['x'])
            y = float(point.attrib['y'])
            center_x.append(x)
            center_y.append(y)

    return center_x, center_y, road_width, lane_count

# 平滑处理道路中心线
def smooth(center_x, center_y):
    x = np.array(center_x)
    y = np.array(center_y)

    t = np.arange(len(x))
    fx = CubicSpline(t, x)
    fy = CubicSpline(t, y)

    ts = np.arange(0, len(x), 0.1)
    xs = fx(ts)
    ys = fy(ts)

    return xs, ys

# 生成参考线
def generate_reference_line(center_x, center_y, lane_count, spacing):
    ref_xs = []
    ref_ys = []

    for i in range(lane_count):
        if i % 2 == 0:
            # 偶数车道在中心线左侧
            offset = i * spacing
        else:
            # 奇数车道在中心线右侧
            offset = - (i + 1) * spacing

        # 根据车道偏移量计算参考线坐标
        ref_x = center_x + offset * np.sin(np.arctan2(np.gradient(center_y), np.gradient(center_x)))
        ref_y = center_y - offset * np.cos(np.arctan2(np.gradient(center_y), np.gradient(center_x)))
        
        # 将参考线添加到列表中
        ref_xs.append(ref_x)
        ref_ys.append(ref_y)

    return ref_xs, ref_ys

# 计算参考线状态信息
def calculate_state(current_pose, reference_line):
    """
    Calculate the current state of the vehicle relative to the reference line.

    Args:
        current_pose (np.ndarray): a 1D array containing the x, y, and yaw of the vehicle.
        reference_line (np.ndarray): an array with shape (N, 3) containing the x, y, and z coordinates of the
            reference line.

    Returns:
        tuple: a tuple containing the lateral error, heading error, and distance along the reference line.
    """
    # Calculate the distance between the vehicle and each point on the reference line.
    distances = np.linalg.norm(reference_line[:, :2] - current_pose[:2], axis=1)

    # Find the index of the closest point on the reference line.
    closest_index = np.argmin(distances)

    # Calculate the lateral error between the vehicle and the reference line.
    lateral_error = np.cross(reference_line[closest_index, :2] - current_pose[:2],
                             reference_line[closest_index + 1, :2] - reference_line[closest_index, :2])
    lateral_error /= np.linalg.norm(reference_line[closest_index + 1, :2] - reference_line[closest_index, :2])

    # Calculate the heading error between the vehicle and the reference line.
    heading_error = current_pose[2] - np.arctan2(reference_line[closest_index + 1, 1] - reference_line[closest_index, 1],
                                                 reference_line[closest_index + 1, 0] - reference_line[closest_index, 0])

    # Calculate the distance along the reference line.
    distance = np.sum(np.linalg.norm(reference_line[1:] - reference_line[:-1], axis=1)[:closest_index]) + \
               np.linalg.norm(reference_line[closest_index, :2] - current_pose[:2])

    return lateral_error, heading_error, distance

def get_lane_boundaries(road, lane_idx):
    """
    Get the left and right lane boundaries for a given lane.

    Args:
        road (opendrive_road): an OpenDrive road object.
        lane_idx (int): the index of the lane to extract the boundaries for.

    Returns:
        dict: a dictionary with keys "left" and "right", each containing a tuple with the x, y, and z coordinates of
            the lane boundary.
    """
    lane = road.lanes[lane_idx]
    left_boundary = road.lanes[lane_idx - 1].border.right_vertices
    right_boundary = lane.border.right_vertices
    return {"left": left_boundary, "right": right_boundary}



def generate_reference_line(road):
    """
    Generate a reference line for a given road using the OpenDrive format.

    Args:
        road (opendrive_road): an OpenDrive road object.

    Returns:
        np.ndarray: an array with shape (N, 3) containing the x, y, and z coordinates of the reference line.
    """
    # Loop through each lane in the road and get its left and right boundaries.
    boundaries = [get_lane_boundaries(road, i) for i in range(1 - len(road.lanes), len(road.lanes))]

    # Convert the boundaries to Cartesian coordinates and concatenate them.
    xy_boundaries = [(boundaries[i]["left"], boundaries[i]["right"]) for i in range(len(boundaries))]
    cartesian_boundaries = [opendrive_utils.xy_to_cartesian(*xy_boundaries[i]) for i in range(len(xy_boundaries))]
    concatenated_boundaries = np.concatenate(cartesian_boundaries, axis=0)

    # Use interpolation to generate a smooth reference line.
    reference_line = interpolate.splprep(concatenated_boundaries.T, k=3, s=2)[0]
    reference_line = interpolate.splev(np.linspace(0, 1, num=500), reference_line)

    return np.array(reference_line).T


