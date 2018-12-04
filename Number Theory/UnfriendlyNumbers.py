#!/bin/python3

def factor(a):
    L = []
    if a > 1:
        p = 2
        lastPrime = 1
        count = 0
        while p*p <= a:
            if a % p == 0:
                if lastPrime == p:
                    count += 1
                else:
                    if lastPrime != 1:
                        L.append( (lastPrime, count) )
                    count = 1
                    lastPrime = p
                a //= p
            elif p == 2:
                p = 3
            else:
                p += 2
        if lastPrime == a:
            L.append( (lastPrime, count+1) )
        else:
            if lastPrime != 1:
                L.append( (lastPrime, count) )
            L.append( (a, 1) )
    return L

def gcd(a,b):
    while b != 0:
        r = a % b
        a = b
        b = r
    return a

def countDivisors(factors):
    prod = 1
    for p, exp in factors:
        prod *= exp+1
    return prod

tokens = input().split()
n = int(tokens[0])
friendly = int(tokens[1])
factors = factor(friendly)

tokens = input().split()
unfriendlies = list( map(int, tokens) )
divisorSet = set([])
for unfriendly in unfriendlies:
    unfriendly = gcd(friendly,unfriendly)
    if unfriendly not in divisorSet:
        L = []
        lim = int(unfriendly**0.5)+1
        for d in range(1,lim):
            if unfriendly % d == 0:
                L.append(d)
                L.append(unfriendly//d)
        divisorSet |= set(L)

print( countDivisors(factors) - len(divisorSet) )
