# Enter your code here. Read input from STDIN. Print output to STDOUT
# Enter your code here. Read input from STDIN. Print output to STDOUT
import math as m
def solve(C, M, n):

    phi = (1+m.sqrt(5))/2
    psi = (1-m.sqrt(5))/2

    phi_2 = 1 + phi
    psi_2 = 1 + psi

    alpha = (C**2 %M)* int((pow(phi_2, 4)/(1+phi_2) + pow(psi_2, 4)/(1+psi_2)))
    S = [alpha%M]
    if(n==1):
        print (0)
    else :
        if(n>2):

            alpha = (C**2%M)*int((pow(phi_2, 5)/(1+phi_2) + pow(psi_2, 5)/(1+psi_2)))


            S.append(alpha%M)

            for k in range(6, 2*n+1):

                alpha = (3*S[-1] - S[-2])

                S.append(alpha %M)

        S = set(S)

        print(len(S))

if __name__ == '__main__':

    data = input()

    C, M, n = list(map(int,data.split(' ')))

    solve(C, M, n)
