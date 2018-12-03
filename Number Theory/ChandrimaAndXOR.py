#!/bin/python3

M = 1000000007
MAX = 10e18

fibonaccis = [1, 2]
i = 0
j = 1
while fibonaccis[j] <= MAX:
    fibonaccis.append(fibonaccis[i] + fibonaccis[j])
    i += 1
    j += 1

powers = [2 ** i for i in range(len(fibonaccis))]


def f(n):
    res = 0
    for i in range(len(fibonaccis) - 1, -1, -1):
        if n >= fibonaccis[i]:
            res += powers[i]
            n -= fibonaccis[i]
    return res


if __name__ == "__main__":
    n = int(input())
    vals = list(map(int, input().split()))
    f_list = [f(i) for i in vals]
    xor_res = 0
    for r in f_list:
        xor_res ^= r
    print(xor_res % M)
