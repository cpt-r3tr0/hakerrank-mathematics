# Enter your code here. Read input from STDIN. Print output to STDOUT
n, m = map(int, input().split())
p = list(map(int, input().split()))

x = 0
while m >= 1:
    m -= 1
    x = p[x]
    if x >= n:
        x += m
        break

print(x)
