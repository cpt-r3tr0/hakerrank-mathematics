#!/bin/python3
n = int(input())
ans = 1
p = int(1e9+7)
s = input().strip().split()
for i in s:
    k = int(i)
    tmp = 1+pow(2,k,p)
    ans*=tmp
    ans%=p
print(ans-1)
