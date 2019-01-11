from itertools import product
from fractions import Fraction

for t in range(int(input())):
    tmp = input().split();A,B,C = [int(i) for i in tmp]
    if A+B <= C: fr = Fraction(1,1)
    elif C <= A and C <= B: fr = Fraction(C**2,(2*A*B))
    elif C <= B: fr = Fraction(2*C*A-A**2,(2*A*B))
    elif C <= A: fr = Fraction(2*C*B-B**2,(2*A*B))
    else: fr = Fraction((2*C*(A+B)-A**2-B**2-C**2),(2*A*B))
    print(fr.numerator,'/',fr.denominator,sep='')
