#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool isSquare(long n)
{
    if(n==1) return true;
    long m = (long)(sqrt(n+4));
    return (m*m==n);
}

long powmodOP(__int128_t a, long p, __int128_t n)
{
    __int128_t ans = 1;
    __int128_t s = a;
    while(p > 0)
    {
        if(p & 1) ans = (ans*s)%n;
        p = p>>1;
        s = (s*s)%n;
    }
    return (long)ans;
}

// uses Miller-Rabin for primality testing.  Guaranteed for n<3.8*10^18
bool isPrime(long n)
{
    int r=0;
    long s;
    int primes[9] = {2,3,5,7,11,13,17,19,23};
    if(n==1) return false;
    if(n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==19 || n==23) return true;
    if((n&1)==0) return false;
    if((n%3)==0 || (n%5)==0 || (n%7)==0) return false;
    while(!(((n-1)>>r) & 1)) r++;
    s = (n-1) >>r;
    __int128_t b = n;
    bool pass;
    for(int i=0; i<9; i++)
    {
        __int128_t q = powmodOP(primes[i], s, b);
        if(q==1) {continue;}
        pass = false;
        for(int j=0; j<r; j++)
        {
        if(q==b-1){pass = true; break;}
        q = (q*q)%b;
        }
        if(!pass) {return false;}
    }
    return true;
}



int main() {
    vector<bool> sieve(100000, true);
    vector<long> pr;
    for(long p = 2; p<100000; p++)
    {
        if(sieve[p])
        {
            pr.push_back(p);
            for(long z = p*p; z<10000; z+=p) sieve[z] = false;
        }
    }
    int n;
    cin >> n;
    vector<int> counts(4,0);
    for(int i=0; i<n; i++)
    {
        long d;
        cin >> d;
        //cerr << d << endl;
        int numpdivpar = 0;
        int sdivpar = 1;
        for(long x : pr)
        {
            long sp = 1;
            if(d%x==0)
            {
                numpdivpar ^=1;
                while(d%x==0)
                {
                    d/=x;
                    sp ^=1;
                }
            }
            if(x>2) sdivpar &= sp;

        }
        if(d>1)
        {
            if(isSquare(d)) numpdivpar ^=1;
            else
            {
                sdivpar = 0;
                if(isPrime(d)) numpdivpar ^=1;
            }
        }
        counts[2*numpdivpar+sdivpar]++;
    }
    cout << max(max(counts[0]+counts[1], counts[1]+counts[3]), max(counts[0]+counts[2], counts[2]+counts[3])) << endl;

    return 0;
}
