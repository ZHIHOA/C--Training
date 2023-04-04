# coding=gbk
import numpy as np
import matplotlib.pyplot as plt
import copy
from celluloid import Camera  # ���涯ͼʱ�ã�pip install celluloid

## �ݹ�ķ�ʽʵ�ֱ���������
def bezier(Ps,n,t):
    """�ݹ�ķ�ʽʵ�ֱ���������

    Args:
        Ps (_type_): ���Ƶ㣬��ʽΪnumpy���飺array([[x1,y1],[x2,y2],...,[xn,yn]])
        n (_type_): n�����Ƶ㣬��Ps�ĵ�һά��
        t (_type_): ����t

    Returns:
        _type_: ��ǰtʱ�̵ı�������
    """
    if n==1:
        return Ps[0]
    return (1-t)*bezier(Ps[0:n-1],n-1,t)+t*bezier(Ps[1:n],n-1,t)


if __name__=='__main__':
    d = 3.5  # ��·��׼���

 # ���Ƶ�
    Ps = np.array([
        [0, -d / 2],
        [25, -d / 2],
        [25, d / 2],
        [50, d / 2]
        ])

    n = len(Ps) - 1  # ���������ߵĽ���

    path=[]  # ·����洢
 # ��������������
    for t in np.arange(0,1.01,0.01):
        p_t = bezier(Ps,len(Ps),t)
        path.append(p_t)
    path = np.array(path)


    ## ��ͼ
    fig = plt.figure(1)
    # plt.ylim(-4, 4)
    camera = Camera(fig)
    len_line = 50  # ������
    # ����ɫ·��ͼ
    GreyZone = np.array([[- 5, - d - 0.5], [- 5, d + 0.5],
                        [len_line, d + 0.5], [len_line, - d - 0.5]])
    for i in range(len(path)):
        # plt.cla()

        plt.fill(GreyZone[:, 0], GreyZone[:, 1], 'gray')
        # ���ֽ���
        plt.plot(np.array([- 5, len_line]), np.array([0, 0]), 'w--')

        plt.plot(np.array([- 5, len_line]), np.array([d, d]), 'w')

        plt.plot(np.array([- 5, len_line]), np.array([- d, - d]), 'w')

        plt.plot(Ps[:, 0], Ps[:, 1], 'ro') # �����Ƶ�
        plt.plot(Ps[:, 0], Ps[:, 1], 'y') # �����Ƶ�����
        # ������������ʾ��Χ
        # plt.axis('equal')
        plt.gca().set_aspect('equal')

        # ����·��
        plt.plot(path[0:i, 0], path[0:i, 1], 'g')  # ·����
        plt.pause(0.5)
    #     camera.snap()
    # animation = camera.animate()
    # animation.save('trajectory.gif')