# Enter your code here. Read input from STDIN. Print output to STDOUT

from math import *
from operator import itemgetter

nTests = int(input())
for t in range(nTests):
    n = int(input())
    a = [int(s) for s in input().split()]
    b = [int(s) for s in input().split()]
    vs = zip(a,b)
    vs = sorted(vs, key=lambda v: atan2(v[1],v[0]))

    best = 0
    for i in range(len(vs)):
        u = vs[i]
        l = u[0]*u[0]+u[1]*u[1]
        for v in (vs+vs)[i+1:(i+len(vs))]:
            tmpU = (u[0]+v[0],u[1]+v[1])
            tmpL = tmpU[0]*tmpU[0]+tmpU[1]*tmpU[1]
            if tmpL >= l:
                u = tmpU
                l = tmpL
        if l > best:
            best = l
        u = vs[i]
        l = u[0]*u[0]+u[1]*u[1]
        for v in reversed((vs+vs)[i+1:(i+len(vs))]):
            tmpU = (u[0]+v[0],u[1]+v[1])
            tmpL = tmpU[0]*tmpU[0]+tmpU[1]*tmpU[1]
            if tmpL >= l:
                u = tmpU
                l = tmpL
        if l > best:
            best = l
    print(best)
    
