#!/usr/bin/python
# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt


if __name__=='__main__':
    
    fig=plt.figure()
    c1_x=[0,0,0,0]
    c1_y=[0,10,20,30]

    c2_x=[0,0,0,0]
    c2_y=[30,40,50,60]

    c3_x=[0,0,0,0]
    c3_y=[60,70,80,90]

    plt.plot(c1_x,c1_y,'ro--',label="c1")
    plt.plot(c2_x,c2_y,'yo--',label="c2")
    plt.plot(c3_x,c3_y,'go--',label="c3")
    plt.plot([1.53577,3.04968,4.55588,6.13353],[0.838995,1.71681,2.60781,1.8505],'bo--',label="reference_line")
    plt.legend()
    plt.show()
    