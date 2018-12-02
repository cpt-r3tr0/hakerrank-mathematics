#!/bin/python3

import sys

def rep(j):
    return (2*pow(10,j)-1)//9

def valid(d):
    if (d == 2) or (d == 3): return 1
    if (d == 5) or (d == 7): return 1
    return 0

def primetest(n):
    if (n == 1):
        return 0
    lim=20
    if n < lim: lim=int(n)
    for i in range(2,lim):
        if (pow(i,n-1,n) != 1):
            return 0
    return 1

def succ(term):
    temp=term
    j=0
    while (temp%10 == 7):
        temp=temp//10
        j=j+1
    d=temp%10
    if (d == 2): return (temp+1)*pow(10,j)+rep(j)
    if (d == 3): return (temp+2)*pow(10,j)+rep(j)
    if (d == 5): return (temp+2)*pow(10,j)+rep(j)
    return rep(j+1)

def legal(first):
    digits=[]
    for i in range(20): digits.append(0)
    temp=first
    len=1
    while (temp > 9):
        temp=temp//10
        len=len+1
    temp=first
    for i in range(1,len+1):
        d=temp%10
        temp=temp//10
        digits[len-i]=d
    answer=0
    for j in range(len):
        d=digits[j]
        if (valid(d) == 1):
            answer=10*answer+d
        else:
            if (d < 7):
                while (valid(d) == 0): d=d+1
                answer=10*answer+d
                return answer*pow(10,len-1-j)+rep(len-j-1)
            else:
                answer=succ(answer)
                return answer*pow(10,len-j)+rep(len-j)
    return answer

first,last = input().strip().split(' ')
first,last = [int(first),int(last)]
term=legal(first)
count=0
while (term <= last):
    if (primetest(term) == 1):
        count=count+1
    term=succ(term)
print(count)    
