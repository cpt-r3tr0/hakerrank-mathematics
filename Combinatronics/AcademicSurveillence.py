# Enter your code here. Read input from STDIN. Print output to STDOUT

mod = 10**9 + 7

for cas in xrange(input()):
    m, n = map(int, raw_input().strip().split())
    ans = 0
    ans += pow(3, m/3, mod) + pow(3, (m+1)/3, mod) + pow(3, (m+2)/3, mod)
    ans += pow(3, 2*m/3, mod) + pow(3, (2*m+1)/3, mod) + pow(3, (2*m+2)/3, mod)
    ans += pow(3, n/3, mod) + pow(3, (n+1)/3, mod) + pow(3, (n+2)/3, mod)
    ans += pow(3, 2*n/3, mod) + pow(3, (2*n+1)/3, mod) + pow(3, (2*n+2)/3, mod)
    ans -= 4*9
    ans += (pow(2, m/3, mod) + pow(2, (m+1)/3, mod) + pow(2, (m+2)/3, mod) - 6) * (pow(3, n/3, mod) + pow(3, (n+1)/3, mod) + pow(3, (n+2)/3, mod) - 9)
    ans += (pow(3, m/3, mod) + pow(3, (m+1)/3, mod) + pow(3, (m+2)/3, mod) - 9) * (pow(2, n/3, mod) + pow(2, (n+1)/3, mod) + pow(2, (n+2)/3, mod) - 6)
    ans -= (pow(2, m/3, mod) + pow(2, (m+1)/3, mod) + pow(2, (m+2)/3, mod) - 6) * (pow(2, n/3, mod) + pow(2, (n+1)/3, mod) + pow(2, (n+2)/3, mod) - 6)
    print ans % mod
