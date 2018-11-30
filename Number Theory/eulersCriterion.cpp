#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long modpow(long long a , long long b , long long m){
    if(a == 0)return 1LL ;
    long long y = a; long long x = 1LL ;

    while(b){
        if(b&1)
            x = (x*y)%m ;
        b /= 2;
        y = (y*y)%m ;

    }
    return x%m ;
}
int main() {
   int t;
    cin>>t;
    long long a, m ;
    while(t--){
        cin>>a>>m;
        if(modpow(a,(m-1)/2 , m) == 1)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
}
