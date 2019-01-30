# Enter your code here. Read input from STDIN. Print output to STDOUT

from math import sqrt

def dist(x1,y1,x2,y2):
    dx = x1 - x2
    dy = y1 - y2
    return sqrt((dx*dx) + (dy*dy))

def test_edge(x,y,edge):
    dx = edge[2] - edge[0]
    dy = edge[3] - edge[1]
    return (((dx*y) - (dy*x)) >= ((dx*edge[1]) - (dy*edge[0])))

def ellipse_range(x,y,ellipse):
    d1 = dist(x,y,ellipse[0], ellipse[1])
    d2 = dist(x,y,ellipse[2], ellipse[3])
    return d1+d2-(ellipse[4]*2)

def solve(edges, ellipses, x1, y1, x2, y2):
    if x2 - x1 < 0.000000001:
        return [x1,y1]      #successful return

    edges2 = []
    for e in edges:
        t1 = test_edge(x1,y1,e)
        t2 = test_edge(x2,y1,e)
        t3 = test_edge(x1,y2,e)
        t4 = test_edge(x2,y2,e)
        if not (t1 or t2 or t3 or t4):
            return None           # all corners outside axis
        if not (t1 and t2 and t3 and t4):
            edges2.append(e)

    ellipses2 = []
    limit = (x2-x1)*1.5
    for e in ellipses:
        r1 = ellipse_range(x1, y1, e)
        r2 = ellipse_range(x2, y1, e)
        r3 = ellipse_range(x1, y2, e)
        r4 = ellipse_range(x2, y2, e)
        if not ((r1<limit) or (r2<limit) or (r3<limit) or (r4<limit)):
            return None           # square outside ellipse
        if not ((r1<0) and (r2<0) and (r3<0) and (r4<0)):
            ellipses2.append(e)


    mx = (x1 + x2) / 2
    my = (y1 + y2) / 2

    ans = solve(edges2,ellipses2,x1,y1,mx,my)
    if ans: return ans
    ans = solve(edges2,ellipses2,mx,y1,x2,my)
    if ans: return ans
    ans = solve(edges2,ellipses2,x1,my,mx,y2)
    if ans: return ans
    ans = solve(edges2,ellipses2,mx,my,x2,y2)
    if ans: return ans

    return None




edges = []
for _ in range(int(input())):
    p = []
    numsides = int(input())
    for _ in range(numsides):
        p.append(list(map(int, input().split())))
    for i in range(numsides):
        edges.append(p[i] + p[(i+1) % numsides])

ellipses = []
for _ in range(int(input())):
    ellipses.append(list(map(int, input().split())))

result = solve(edges, ellipses, -65536, -65536, 65536, 65536)
print(result[0])
print(result[1])
