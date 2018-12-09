# Enter your code here. Read input from STDIN. Print output to STDOUT

from collections import Counter

MOD = 1000003
cache = {}
fact,invFact = [1]+(MOD-1)*[0], [1]+(MOD-1)*[0]
for k in xrange(1,MOD-1+1):
    fact[k] = fact[k-1]*k % MOD
invFact[MOD-1] = pow(fact[MOD-1],MOD-2,MOD)
for k in xrange(MOD-1,1,-1):
    invFact[k-1] = invFact[k]*k % MOD

def comb(n, k, MOD):
    if k < 0: return 0
    if k > n: return 0
    if k==0 or k==n: return 1
    if n < MOD: return (fact[n] * invFact[k] * invFact[n-k]) % MOD
    else: return (comb(n/MOD, k/MOD, MOD)*comb(n%MOD,k%MOD,MOD)) % MOD

def rec(n,k,C,letter,used):
    key = (letter,used)
    if letter > 'Z': return 1
    if key in cache: return cache[key]
    ans = rec(n,k,C,chr(ord(letter)+1),used)
    for i in xrange(1,C[letter]+1):
        ans += comb(n-used-k*(i-1), i, MOD) * rec(n,k,C,chr(ord(letter)+1),used+i) % MOD
    cache[key] = ans % MOD
    return cache[key]

n,k = map(int,raw_input().split())
print rec(n,k,Counter(raw_input()),'A',0)
