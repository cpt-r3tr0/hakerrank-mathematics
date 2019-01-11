#!/bin/python

# Enter your code here. Read input from STDIN. Print output to STDOUT

from math import factorial

n = input()
count =[0 for i in range(101)]

a = map(int, raw_input().split())

for i in a:
    count[i]+=1

ans = factorial(n)

for j in range(1,101):
    ans/=factorial(count[j])

if a==sorted(a):
    print "0.000000"
else:
    print "%0.6f"%(ans)
