# Enter your code here. Read input from STDIN. Print output to STDOUT
MAXA = 10**7

def main():
    ncases = int(input())
    for _ in range(ncases):
        n = int(input())
        a = [int(f) for f in input().split()]
        assert n == len(a)
        print(mindegree(a))

def mindegree(a):
    factors = [set(factoroddpow(item)) for item in a]
    adjoins = 0
    for i, factor in enumerate(factors):
        if len(factor)==0:
            continue
        sample = next(iter(factor), None)
        for otherfactor in factors[i+1:]:
            if sample in otherfactor:
                otherfactor ^= factor
        adjoins += 1
    return 1 << adjoins

def allprimes(upto):
    primes = []
    seive = [True] * (upto+1)
    for i in range(2, upto+1):
        if seive[i]:
            primes.append(i)
            for j in range(i*i, upto+1, i):
                seive[j] = False
    return primes

def factoroddpow(n, primelist = allprimes(int(MAXA**0.5))):
    ans = []
    for prime in primelist:
        if n % prime == 0:
            deg = 0
            while n % prime == 0:
                n //= prime
                deg += 1
            if deg & 1 == 1:
                ans.append(prime)
    if n > 1:
        ans.append(n)
    return ans

main()
