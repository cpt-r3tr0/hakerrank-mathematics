#include <iostream>
using namespace std;

long modulus_of_power(long a, long x, long p) {

    long res = 1;
    while(x > 0) {
        if( x % 2 != 0) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }
    return res;
}

long modulus_of_ncr(long n, long k, long p) {

    long num = 1;
    for (int i=0; i<k; i++) {
        num = (num * (n-i) ) % p;
    }

    long den = 1;
    for (int i=1; i<=k; i++) {
        den = (den * i) % p;
    }

    return ( num*modulus_of_power(den, p-2, p)) % p;
}
int main()
{
     int t;
     long x=1000000007,n,m;
    cin>>t;
    while(t-->0)
    {
        cin>>n>>m;
        cout<<modulus_of_ncr(m+n,m,x)<<endl;
    }


    return 0;
}
