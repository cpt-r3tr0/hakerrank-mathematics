import math

def normalize(X):
    rv = X[0]
    for x in X[1:]:
        rv = math.gcd(rv,x)
        if rv == 1:
            break
    return rv

n, q = (int(x) for x in input().split())
A = list(set([int(x) for x in input().split()]))
base = normalize(A)
for _ in range(q):
    t = int(input())
    if len(A) == 1:
        print(base + t)
    else:
        print(math.gcd(t,base))
