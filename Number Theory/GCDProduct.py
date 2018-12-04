#!/bin/python3

N, M = map(int, input().split())
lim = min(N,M) + 1
mark = bytearray(lim >> 1)
primes = [2]
for i in range(3,lim,2):
   if mark[i>>1]: continue
   primes.append(i)
   for j in range(3*i,lim,2*i):
      mark[j>>1] = 1
mod = 10**9 + 7
prod = 1
for p in primes:
   q = p
   while q < lim:
      prod = (prod * pow(p, (N//q)*(M//q), mod)) %mod
      q *= p
print(prod)
