#!/usr/bin/python
# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline

# 生成样本数据
num_points = 100
s_frenet = np.linspace(0, 10, num_points)
xy_frenet = np.zeros((num_points, 2))
xy_frenet[:, 0] = s_frenet
xy_frenet[:, 1] = np.sin(s_frenet)

# 进行样条插值
cs = CubicSpline(s_frenet, xy_frenet[:num_points,:])

# 可视化结果
s_eval = np.linspace(0, 10, num_points*10)
xy_eval = np.zeros((num_points*10, 2))
xy_eval[:, 0] = s_eval
xy_eval[:, 1] = cs(s_eval)

plt.plot(xy_frenet[:, 0], xy_frenet[:, 1], 'o', label='data points')
plt.plot(xy_eval[:, 0], xy_eval[:, 1], label='cubic spline')
plt.legend()
plt.show()
