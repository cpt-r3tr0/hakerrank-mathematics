#include <bits/stdc++.h>

using namespace std;

// /*
//  * Complete the primeCount function below.
//  */
// long long a[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
// int primeCount(long n) {
//     /*
//      * Write your code here.
//      */
//     long long p=1;
//         int i=0;
//         while(p<=n) {
//             p=p*a[i];
//             i++;
//         }
//     return (i-1);
// }

// int main()
// {
//     ofstream fout(getenv("OUTPUT_PATH"));

//     int q;
//     cin >> q;
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');

//     for (int q_itr = 0; q_itr < q; q_itr++) {
//         long n;
//         cin >> n;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');

//         int result = primeCount(n);

//         fout << result << "\n";
//     }

//     fout.close();

//     return 0;
// }
unsigned long long int gcd(unsigned long long int a, unsigned long long int b)
{

    while (b) {
        unsigned long long int t = b;

        b = a % b;
        a = t;
    }
    return a;
}

unsigned int max_unique_primes(unsigned long long int n)
{
    unsigned int count;
    unsigned long long int prod;
    unsigned long long int prim;

    if (n < 2)
        return 0;

    prod = 2;
    count = 1;
    for (prim = 3; prod * prim <= n; prim += 2) {
        if (gcd(prod, prim) == 1) {
            prod *= prim;
            count++;
        }
    }
    return count;
}

int main(void)
{
    unsigned int q;

    if (scanf("%u", &q) != 1)
        return EXIT_FAILURE;

    while (q--) {
        unsigned long long int n;

        if (scanf("%llu", &n) != 1)
            return EXIT_FAILURE;

        printf("%u\n", max_unique_primes(n));
    }
    return EXIT_SUCCESS;
}
