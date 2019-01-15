# Enter your code here. Read input from STDIN. Print output to STDOUT
from random import *
import re
import sys
import math
import fractions


k,n = raw_input().split()
k = int(k)
n = int(n)

if k==1:
    c=(n-2)*2
    p=3
    g=fractions.gcd(p,c)
    print "%d / %d"%(c/g,p/g)
    exit(0)

if k==2:
    c = 8*(n-3)*(5*(n-3)+12)+59
    p = 90
    g=fractions.gcd(p,c)
    print "%d / %d"%(c/g,p/g)
    exit(0)

if k==3:
    i = n-3
    c = i*(56*i*(5*i+21)+1559)*2/3+410
    p = 315*2
    g=fractions.gcd(p,c)
    print "%d / %d"%(c/g,p/g)
    exit(0)

if k==4:
    i = n-3
    c = (4*i*(i*(140*i*(5*i+32)+9731)+8204)+9435)*2/3
    p = 4725*2
    g=fractions.gcd(p,c)
    print "%d / %d"%(c/g,p/g)
    exit(0)

if k==5:
    n = n-3
    c = 4* (n* (44* n* (n* (140* n* (n+9)+4001)+5433)+141769)+30705)/3
    p =  31185*2
    g=fractions.gcd(p,c)
    print "%d / %d"%(c/g,p/g)
    exit(0)



ct = [0] * (n+1)
ct[1] = 2
p = 2
ans = []
for i in range(3,n+1):
    p *= i
    nt = [0] * (i+2)
    nt[1] = ct[1] + 2 * ct[0]
    for j in range(2,i+1):
        nt[j] = j*ct[j] + 2 * ct[j-1] + (i-j)*ct[j-2]

    ct = nt
    ch = 0
    for i in range(len(ct)):
        ch += ((i-1)**k) * (ct[i])
    g = fractions.gcd(p,ch)
    assert 31185*2%(p/g)==0

    mu = 31185*2/(p/g)
    ans.append(ch/g*mu)
    print "%d / %d"%(ch/g*mu,p/g*mu)

#exit(0)
def kaisa(arr):
    ret=[]
    for i in range(len(arr)-1):
        ret.append(arr[i+1]-arr[i])
    return ret
#ans = kaisa(ans)
#ans = kaisa(ans)
#ans = kaisa(ans)
#ans = kaisa(ans)
for i in range(len(ans)-1):
    n=i
    print i,ans[i+1]-ans[i],ans[i],4 *(44 *n* (n* (140* n* (5* n+46)+20963)+28609)+618465)/3

# 352* (n *(280* n* (5* n+42)+32023)+28356)/3


#print ct
ch = 0
for i in range(len(ct)):
    ch += ((i-1)**k) * (ct[i])


g = fractions.gcd(p,ch)
print "%d / %d"%(ch/g,p/g)
