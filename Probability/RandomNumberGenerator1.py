# Enter your code here. Read input from STDIN. Print output to STDOUT

maxn = 10**6+10
dp = [0.0]*maxn
for i in range(1,maxn):
    dp[i] = dp[i-1]+1.0/i
def k_val(m,n):
    return m-((n-m-1.0)/(dp[n]-dp[m-1]));
# solve for m-k >=0
def sum(m,n):
    return (n*(n+1))/2-(m*(m-1))/2
def bin_search(i,j,n):
    if(k_val(i,n)>=0):
        return i
    if(k_val(i+1,n)>=0):
        return i+1
    h = (i+j)/2
    if(k_val(h,n)>=0):
        return bin_search(i,h,n)
    return bin_search(h,j,n)
def ans(n):
    if(n==1):
        return 0.0
    m = bin_search(1,n,n)
    x = m-k_val(m,n)
    return (sum(m,n)/2.0-(x*x*(dp[n]-dp[m-1]))/2)/(2.0*n-1)
for t in range(0,input()):
    print '%.20f' % ans(input())        
