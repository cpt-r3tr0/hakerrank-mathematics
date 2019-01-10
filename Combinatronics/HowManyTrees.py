# Enter your code here. Read input from STDIN. Print output to STDOUT

import sys
P = 10**9 + 7

def f(n, k):

    # k non-leaves
    if n == 2:
        return 1 if k == 0 else 0


    def C(n, k):
        return fact[n] * inv_fact[k] % P * inv_fact[n - k] % P

    fact = [1]
    for i in range(1, n + 1):
        fact.append(fact[-1] * i % P)

    inv = [0, 1]
    for i in range(2, n + 1):
        inv.append(P - P // i * inv[P % i] % P)
    inv_fact = [1]
    for i in range(1, n + 1):
        inv_fact.append(inv_fact[-1] * inv[i] % P)

    ret = 0
    for used in range(1, k + 1):
        delta = C(k, used) * pow(used, n - 2, P) % P
        # print(used, delta, file=sys.stderr)
        if used & 1 == k & 1:
            ret += delta
        else:
            ret -= delta
    return (ret % P) * C(n, k) % P

n, l = map(int, input().split())
k = n - l
print(f(n, k))
