# Enter your code here. Read input from STDIN. Print output to STDOUT

MAX_N = 500

def precompute_combin(n):
    c = [[None for _j in xrange(i + 1)] for i in xrange(n + 1)]
    for i in xrange(n + 1):
        c[i][i] = c[i][0] = 1
    for i in xrange(2, n + 1):
        for j in xrange(1, i):
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1]
    return c

_combin = precompute_combin(MAX_N)

def combin(n, k): return _combin[n][k]

def memoize(f):
    """ Memoization decorator for functions taking one or more arguments. """
    class memodict(dict):
        def __init__(self, f):
            self.f = f
        def __call__(self, *args):
            return self[args]
        def __missing__(self, key):
            ret = self[key] = self.f(*key)
            return ret
        @property
        def func_name(self): return self.f.func_name
    return memodict(f)

from operator import mul

@memoize
def big_combin(m, k):
    def prod(a): return reduce(mul, a, 1)
    return prod(xrange(m - k + 1, m + 1)) / prod(xrange(1, k + 1))

@memoize
def s_nomial(m, k, s):
    def f(i):
        t = combin(m, i) * combin(m + k - s * i - 1, m - 1)
        return -t if i % 2 else t
    if k > m * (s - 1): return 0
    return sum(f(i) for i in xrange(min(m, k / s) + 1))

def divide(a, b): return 10 ** 20 * a / b * 10 ** -20

def solve(m, n):
    def F(m, n, k):
        if n > m:
            return sum(big_combin(n, l) * s_nomial(l, m - l, k) for l in xrange(1, m + 1))
        else:
            return s_nomial(n, m, k + 1)
    return divide(m * F(m, n, m) - sum(F(m, n, k) for k in xrange(1, m)), big_combin(m + n - 1, m))

if __name__ == "__main__":
    def main():
        for _ in xrange(input()):
            m, n = map(int, raw_input().split())
            print solve(m, n)
    main()
