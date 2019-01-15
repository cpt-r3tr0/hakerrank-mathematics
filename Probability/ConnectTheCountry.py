# Enter your code here. Read input from STDIN. Print output to STDOUT
from __future__ import division
import math
import operator
import sys
def prod(lst):
    return reduce(operator.mul, lst)

def connectivitymatrix(n):
    return [[0 for i in range(n)]  for i in range(n)]

def printmatrix(m):
    for n in m:
        print(n)

def possibleconnections(m):
    n=len(m)
    return (sum(sum(m[i][j]==0 for j in range(i)) for i in range(n)))

def nbedges(n):
    return n*(n-1)//2

def stateedges(state):
    return sum(n for p,n in state)

def increasedict(d, key, n):
    if key in d:
        d[key]+=n
    else:
        d[key]=n

def statepoints(state):
    return sum(p for p,n in state)

def nextstates(state,nb,n):
    ncc = len(state)
    result=dict()
    #next state by adding new component
    nbfree = n-statepoints(state)
    if nbfree>=2:
        nbnew = nbedges(nbfree)*nb
        result[tuple(sorted(state+((2,1),)))] = nbnew
    for i in range(ncc):
        # Next state based on one component
        #add edge inside component
        comp = state[i]
        nbfce = nbedges(comp[0]) - comp[1] #nb of free edges in component
        if nbfce>=1:
            increasedict(result, \
                         tuple(sorted(state[:i]+state[i+1:]+((comp[0],comp[1]+1),))),\
                         nb * nbfce)
        #add edge by extending component
        if nbfree >= 1:
            increasedict(result, \
                         tuple(sorted(state[:i]+state[i+1:]+((comp[0]+1,comp[1]+1),))),\
                         nb * comp[0] * nbfree)
        for j in range(i):
            # Connect two component (j<i)
            comp2 = state[j]
            increasedict(result, \
                         tuple(sorted(state[:j]+state[j+1:i]+state[i+1:] \
                                    + ((comp[0]+comp2[0],comp[1]+comp2[1]+1),))), \
                         nb * comp[0]*comp2[0])
    return result


def allnextstates(cstates,n):
    nstates = dict()
    states = cstates.items()
    for state,nb in states:
        newstates = nextstates(state,nb,n)
        for newstate,nbnewstate in newstates.items():
            increasedict(nstates, newstate,nbnewstate)
    return nstates

def nbdiffsols(n, it):
    N = nbedges(n)
    return prod(i for i in range(N-it+1,N+1))

def removefinished(allstates,n):
    nbtotal = -1
    result = 0
    toremove = []
    for state in allstates:
        if state[0][0]==n:
            if nbtotal < 0:
                nbtotal = nbdiffsols(n,state[0][1])
            result += state[0][1]*allstates[state]/nbtotal
            toremove.append(state)
    for r in toremove:
        allstates.pop(r)
    return result
def expectedcons(n):
    if n<2:
        return 0
    elif n == 2:
        return 1
    if n<= 10:
        result = 0
        cstates=dict()
        cstates[((2,1),)]=nbedges(n)
        while len(cstates)>0:
            cstates = allnextstates(cstates,n)
            result += removefinished(cstates,n)
        return result
    result = expectedcons(10)
    for i in range(11,n+1):
        result += math.log(i)*0.5909757109+0.4020065009
    return result

N = int(sys.stdin.readline())
print(int(expectedcons(N)))
