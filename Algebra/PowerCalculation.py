#!/bin/python3

import os
import sys

M = { (k%4, k%25): k for k in range(100)}
# Complete the solve function below.
def solve(k, n):
    # modulus to 4 first, odd zero, even 2
    if n%2 == 0:
        m4 = 2
    else:
        m4 = 0
    # modulus to 25, 4 for 20
    if n%4 == 0:
        m25 = 20
    else:
        m25 = 0
    S4 = 0
    r4 = k%4
    q4 = k//4
    for j in range(1,r4+1):
        S4 += pow(j, n, 4)
    S4 = (S4 + q4*m4)%4
    S25 = 0
    r25 = k%25
    q25 = k//25
    for j in range(1, r25+1):
        S25 += pow(j, n, 25)
    S25 = (S25 + q25*m25)%25
    r100 = M[(S4, S25)]
    if r100<10:
        return '0'+str(r100)
    else:
        return str(r100)
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        kn = input().split()

        k = int(kn[0])

        n = int(kn[1])

        result = solve(k, n)

        fptr.write(result + '\n')

    fptr.close()
