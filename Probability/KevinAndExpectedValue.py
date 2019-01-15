from __future__ import division, print_function

# zeta(-1/2,1/4)
z = 0.0903222587612462438741957208084171215210703209418806

# precalculate small S(n)
L = 10000
S_small = [0]*L
S_small[0] = 1/2
for n in xrange(1,L):
    S_small[n] = S_small[n-1] + (n + 1/4)**(1/2)

def S(n):
    if n < L:
        return S_small[n]
    else:
        return 2/3*n**(3/2) + 3/4*n**(1/2) + z + 23/192*n**(-1/2) - 5/512*n**(-3/2)

def f(N):
    return 1/(2*N) * (N-2+2*S(N-1))

for cas in xrange(input()):
    print(f(input()))
