M = 10**9 + 7

def f(k, n):
    res = 0
    i = 1
    while i <= n:
        res += i
        res %= M
        i *= k
        i += 1
    return res

def sum_f(k, n):
    res = 0
    lo = 0
    hi = 1
    while 1:
        cnt = max(0, min(hi, n+1) - lo)
        cnt %= M
        res += cnt * f(k, lo)
        res %= M
        lo = lo * k + 1
        hi = hi * k + 1
        if(lo > n):
            break
    return res

Q = 10**5
K = 10**5
R = 10**18

q = int(raw_input())
assert(q >= 1 and q <= Q)

for _ in xrange(q):
    k, l, r = map(int, raw_input().split())
    assert(k >= 2 and k <= K)
    assert(l >= 1 and l <= r)
    assert(r <= R)

    res = sum_f(k, r) - sum_f(k, l-1)
    res %= M
    print res
