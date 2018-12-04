# Enter your code here. Read input from STDIN. Print output to STDOUT

from itertools import combinations
from fractions import gcd

def ls_mul(a, b):
    def lcm(s): return reduce(lambda x, y: x * y / gcd(x, y), s)

    def sieve(k):
        f = [False] * k + [True] * (a - k + 1)
        for i in xrange(k, a + 1):
            if f[i]: f[i + i:a + 1:i] = [False] * ((a - i) / i)
        return [i for i in xrange(k, a + 1) if f[i]]

    def mul(op):
        def mul_any(n, factors):
            def mul_combins(m):
                return sum(op(n, lcm(f)) for f in combinations(factors, m))
            return sum([1, -1][i % 2] * mul_combins(i + 1)
                    for i in xrange(len(factors)))

        def mul_range(k):
            factors = sieve(k)
            return mul_any(b * k, factors) - mul_any(b * (k - 1), factors)

        return sum(mul_range(k) for k in xrange(1, a + 1))

    def count_mul():
        def f(n, mult): return n / mult
        return mul(f)

    def sum_mul():
        def f(n, mult):
            k = n / mult
            return mult * k * (k + 1) / 2
        return mul(f)

    return count_mul(), sum_mul()

def mask(x):
    k = 0
    while x >> k: k += 1
    return (1 << k) - 1

def ls_xor(a, b):
    m = mask(a)
    q = b & m
    t = (b & ~m)
    s = set([x ^ y for x in xrange(q + 1) for y in xrange(1, a + 1)])

    def count_xor():
        if q == b:
            return len(set([x ^ y for x in xrange(1, a + 1) for y in xrange(1, b + 1)]))
        else:
            return t + len(s) - (a == 1)

    def sum_xor():
        if q == b:
            return sum(set([x ^ y for x in xrange(1, a + 1) for y in xrange(1, b + 1)]))
        else:
            return t * (t - 1) / 2 + t * len(s) + sum(s) - (a == 1)

    return count_xor(), sum_xor()

def count_digits(x):
    n = 1
    x /= 10
    while x:
        n += 1
        x /= 10
    return n

def solve(a, b):
    nm, sm = ls_mul(a, b)
    nx, sx = ls_xor(a, b)
    return nx * sm * 10 ** (count_digits(b) + 1) + nm * sx

if __name__ == "__main__":
    def main():
        a, b = map(int, raw_input().split())
        print solve(a, b)
    main()
