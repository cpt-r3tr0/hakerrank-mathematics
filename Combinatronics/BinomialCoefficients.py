# Enter your code here. Read input from STDIN. Print output to STDOUT

from collections import Counter

def main():
    ncases = int(input())
    for _ in range(ncases):
        n, p = [int(fld) for fld in input().split()]
        m = count(n, p)
        print(' '.join(map(str, m)))

def count(n, p):
    d = []
    nn = n
    while nn != 0:
        d.append(nn % p)
        nn //= p
    pprev = Counter()
    nprev = Counter([0])
    for di in d:
        ncur = (Counter({k: di*v for k, v in pprev.items()}) +
            Counter({k: (di+1)*v for k, v in nprev.items()}))
        pcur = (Counter({k+1: (p-di)*v for k, v in pprev.items()}) +
            Counter({k+1: (p-di-1)*v for k, v in nprev.items()}))
        pprev, nprev = pcur, ncur
    return [ncur[i] for i in range(1 + max(ncur.keys()))]


def oldcount(n, p):
        m = Counter()
        for k in range(n+1):
            m[factorcount(comb(n, k), p)] += 1
        return [m[i] for i in range(1+max(m.keys()))]

def comb(n, k):
    assert 0 <= k <= n
    ans = 1
    for i in range(k):
        ans = ans * (n - i) // (i+1)
    return ans

def factorcount(x, p):
    assert x > 0
    ans = 0
    while x % p == 0:
        ans += 1
        x //= p
    return ans

main()
