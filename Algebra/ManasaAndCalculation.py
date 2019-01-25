# Enter your code here. Read input from STDIN. Print output to STDOUT

def bitize(x):
    L = []
    while(x > 0):
        L.append(x % 2)
        x //= 2
    if not L:
        L = [0]
    return L

def pow_mod(a,b,m):
    b_bits = bitize(b)
    a_powers = [0 for x in b_bits]
    a_powers[0] = a % m
    if b_bits[0]:
        total = a % m
    else:
        total = 1
    for i in range(1, len(b_bits)):
        a_powers[i] = (a_powers[i - 1] * a_powers[i - 1] )% m
        if b_bits[i]:
            total *= a_powers[i]
            total %= m
    return total

N = int(input())

prime_power_list = []

for i in range(0,N):
    pab = [int(a) for a in input().split()]
    prime_power_list.append(pab)

modulus = pow(10,9) + 7
total_product = 1
all_are_equal = True

for i in range(0, N):

    if prime_power_list[i][1] == prime_power_list[i][2]:
        prod_i = pow_mod(prime_power_list[i][0], prime_power_list[i][1], modulus)
    else:
        all_are_equal = False
        prod_i = pow_mod(prime_power_list[i][0], prime_power_list[i][1], modulus) + pow_mod(prime_power_list[i][0], prime_power_list[i][2], modulus)
    total_product *= prod_i
    total_product %= modulus

if all_are_equal:
    total_product *= 2
    total_product %= modulus
print(total_product)
