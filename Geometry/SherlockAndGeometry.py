#!/bin/python3

import os
import sys
import math

def draw_triangle(xc, yc, R, t1,t2,t3):
    arr = [t1,t2,t3]
    x = y_circle(yc,xc,R)[0]
    y = y_circle(yc,xc,R)[1]
    plt.plot(x, y, 'b--')
    plt.plot(x, 2*yc-y, 'b--')
    ms = {}
    pts = {}
    pt_dists = {}

    for z in [[0,1],[0,2],[1,2]]:
        i = z[0]
        j = z[1]
        x1 = arr[i][0]
        y1 = arr[i][1]
        x2 = arr[j][0]
        y2 = arr[j][1]


        x_min = min(x1,x2)
        x_max = max(x1,x2)
        x = np.arange(x_min, x_max, 0.2)

        if x1 == x2:
            y = np.arange(y1, y2, 0.2)
            x = [x1]*len(y)
            m = 9e10000000000000
        else:
            y = y_triangle(x1,x2,y1,y2, x)
            m = (y1-y2)/(x1-x2)

        xp = np.arange(-10, 20, 0.2)
        yp = perp_line(xc,yc,m,xp)

        if x1 == x2:
            min_pt = [x1, yc]
        elif y1 == y2:
            min_pt = [xc, y1]
        else:
            min_pt = min_dist_from_point(m,y1 - m * x1,xc,yc)

        pt_dist = math.sqrt((min_pt[0]-xc)*(min_pt[0]-xc) + (min_pt[1]-yc)*(min_pt[1]-yc))

        if (min_pt[0] < min(x1,x2) or min_pt[0] > max(x1,x2)):
            v1 = math.sqrt((x1-xc)*(x1-xc) + (y1-yc)*(y1-yc))
            v2 = math.sqrt((x2-xc)*(x2-xc) + (y2-yc)*(y2-yc))
            if v1 < v2:
                min_pt[0] = x1
                min_pt[1] = y1
                pt_dist = v1
            else:
                min_pt[0] = x2
                min_pt[1] = y2
                pt_dist = v2

        # red dashes, blue squares and green triangles
        plt.plot(x, y, 'r-')
        #plt.plot(xp, yp, 'g-')
        plt.plot(min_pt[0], min_pt[1], 'g^')
        ms[(i,j)] = m
        pts[(i,j)] = min_pt
        pt_dists[(i,j)] = pt_dist
    #plt.xlim([-10,20])
    #plt.ylim([-10,20])
    plt.show()
    #print(ms)
    #print(pt_dists)

def y_triangle(x1,x2,y1,y2,x_in):
    m = (y1-y2)/(x1-x2)
    b = y1 - m * x1
    return m*x_in + b

def perp_line(xc,yc,m1,x):
    if m1 == 0:
        m1 = 1e-100
    m = -1/m1
    b = yc + xc/m1
    y = m*x+ b
    return y

def min_dist_from_point(m1,b1,xc,yc):
    m2 = -1/m1
    b2 = yc + xc/m1

    xo =-(b1-b2)/(m1-m2)
    yo = m1*(b2-b1)/(m1-m2) + b1

    vec = [xo,yo]
    #print('vec: ')
    #print(vec)
    return vec

def solve(xc, yc, R, t1, t2, t3, pr = 0):
    arr = [t1,t2,t3]
    xs = [z[0] for z in arr]
    x_left = min(xs)
    x_right = max(xs)

    ys = [z[1] for z in arr]
    y_bottom = min(ys)
    y_top = max(ys)

    if pr == 1:
        print(x_left)
        print(x_right)
        print(y_top)
        print(y_bottom)

    ms = []
    pts = []
    pt_dists = []

    for z in [[0,1],[0,2],[1,2]]:
        i = z[0]
        j = z[1]
        x1 = arr[i][0]
        y1 = arr[i][1]
        x2 = arr[j][0]
        y2 = arr[j][1]

        if x1 == x2:
            m = 9e100000000
        else:
            m = (y1-y2)/(x1-x2)

        if x1 == x2:
            min_pt = [x1, yc]
        elif y1 == y2:
            min_pt = [xc, y1]
        else:
            min_pt = min_dist_from_point(m,y1 - m * x1,xc,yc)

        pt_dist = math.sqrt((min_pt[0]-xc)*(min_pt[0]-xc) + (min_pt[1]-yc)*(min_pt[1]-yc))

        if (min_pt[0] < min(x1,x2) or min_pt[0] > max(x1,x2)):
            v1 = math.sqrt((x1-xc)*(x1-xc) + (y1-yc)*(y1-yc))
            v2 = math.sqrt((x2-xc)*(x2-xc) + (y2-yc)*(y2-yc))

            if v1 < v2:
                min_pt[0] = x1
                min_pt[1] = y1
                pt_dist = v1
            else:
                min_pt[0] = x2
                min_pt[1] = y2
                pt_dist = v2

        ms.append(m)
        pts.append(min_pt)
        pt_dists.append(pt_dist)

    v_dist = [math.sqrt((z[0]-xc)*(z[0]-xc) + (z[1]-yc)*(z[1]-yc)) for z in arr]

    if pr == 1:
        print('vertice dist from circle centre')
        print(v_dist)
        print('point dist from circle centre')
        print(pt_dists)

    if (x_left > xc + R):
        return 'NO'
    elif (x_right < xc - R):
        return 'NO'
    elif (y_top < yc - R):
        return 'NO'
    elif (y_bottom > yc + R):
        return 'NO'
    elif (R > v_dist[0] and R > v_dist[1] and R > v_dist[2] ):
        return 'NO'
    elif ((R < v_dist[0] and R < v_dist[1] and R < v_dist[2]) and
     (pt_dists[0] > R and pt_dists[1] > R and pt_dists[2] > R)):
        return 'NO'
    return 'YES'

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        xyr = input().split()

        x = int(xyr[0])

        y = int(xyr[1])

        r = int(xyr[2])

        t1 = list(map(int, input().rstrip().split()))

        t2 = list(map(int, input().rstrip().split()))

        t3 = list(map(int, input().rstrip().split()))

        result = solve(x, y, r, t1, t2, t3)

        fptr.write(result + '\n')

    fptr.close()
