def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a%b)
def gcdapp(arr, ind):
    if(len(arr) == 1):
        if arr[ind] == 1:
            return 1
        else:
            return 0
    elif ind == len(arr)-2:
        return gcd(arr[ind], arr[ind+1])
    return gcd(arr[ind], gcdapp(arr, ind+1))
testcase = int(input())
for x in range(testcase):
    size = int(input())
    arr = [int(x) for x in input().strip().split(' ')]
    if(gcdapp(arr, 0) == 1):
        print("YES")
    else:
        print("NO")
    
