P = 1000000009

def quadratic(H,X):
    '''
    compute sum(H[i]H[j] |X[i]-X[j]| , i < j)
    '''
    n = len(H)

    # sort H and X such that X is in non-increasing order
    X, H = zip(*sorted(zip(X, H), reverse=True))

    # diff[i] = sum(H[j], j > i) - sum(H[j], j < i)
    diff = [ sum(H[1:]) ]
    for i in range(1,n):
        diff.append( diff[-1] - H[i-1] - H[i] )

    return sum( H[i]*X[i]*diff[i] for i in range(n) ) % P

# read the input
n, d = map(int, input().split())
H = [None] * n
X = [None] * n
for i in range(n):
    row = list(map(int, input().split()))
    H[i] = row[0]
    X[i] = row[1:]

print( sum(quadratic(H, [x[j] for x in X]) for j in range(d)) % P )
