# Enter your code here. Read input from STDIN. Print output to STDOUT

def all(n):
    if n%2 == 1:
        no = n*(n-1)/2
    else:
        no = n*(n/2-1)
    if n%3 == 0:
        no -= n/3*2
    return(no)
def non(a,n):
    if n%2 == 1:
        s0 = s1 = 0
        i = 0
        while i < n:
            if a[i] == '0':
                s0 += 1
            else:
                s1 += 1
            i += 1
        s = s0*s1*6
        if(n%3 == 0):
            n1 = n/3
            n2 = n1*2
            i = 0
            while i<n:
                if a[i] != a[int((i+n1)%n)]:
                    s -= 2
                if a[i] != a[int((i+n2)%n)]:
                    s -= 2
                i += 1
    else:
        s00 = s01 = s10 = s11 = s = 0
        i = 0
        while i <n:
            if a[i] == '0':
                s00 += 1
            else:
                s01 += 1
            i += 2
        i = 1
        while i < n:
            if a[i] == '0':
                s10 += 1
            else:
                s11 += 1
            i += 2
        s += s00 * s01 * 8
        s += s10 * s11 * 8
        s += s00 * s11 * 4
        s += s10 * s01 * 4
        n1 = n/2
        i = 0
        while i < n:
            if a[i] != a[int((i + n1)%n)]:
                s -= 2
            i += 1
        if n%3 == 0:
            n1 = n/3
            n2 = n1*2
            i = 0
            while i < n:
                if a[i] != a[int((i+n1)%n)]:
                    s -= 2
                if a[i] != a[int((i+n2)%n)]:
                    s -= 2
                i += 1
    return(s/2)
t = int(input())
for x in range(t):
    a = input()
    n = len(a)
    no = all(n) - non(a,n)/2
    print('Case',x+1,end = '')
    print(':',int(no))
