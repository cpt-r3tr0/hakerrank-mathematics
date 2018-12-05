#include <bits/stdc++.h>

using namespace std;



long long eps_power(int n, int mod){
    if(n==1) return 2;
    if(n%2==0){
        long long x = eps_power(n/2,mod);
        return (x*x) % mod;
    } else {
        long long x = eps_power(n/2,mod);
        return ((x*x) % mod )*2 %mod;
    }
}

double fraction(long double n){
    return n - floor(n);
}


long long eps(int n, int k){
    long double constant = 0.30102999566398119521373889472449L;
    long double value = pow(10.0,fraction(n*constant));
    long double fix = pow(10.0, k-1);
    return (long long)floor(value*fix);
}

int main(){
    int test;
    cin >> test;
    while(test--){
        int n, k;
        cin >> n;
        n = n-1;
        cin >> k;
        int mod = pow(10.0,k);
        if(n > log2(double(mod)))
            cout << eps_power(n,mod) + eps(n,k) << endl;
        else
            cout << 2 * eps_power(n,mod) << endl;
    }
    return 0;
}
