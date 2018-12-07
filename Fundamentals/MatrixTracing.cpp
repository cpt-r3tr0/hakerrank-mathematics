#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll fact[2100000];
ll mod = 1000000007;

ll pow_(ll a, ll b, ll m){
    ll ans=1;
    while(b){
        if(b&1) ans = ans*a%m;
        b=b>>1;
        a=a*a%m;
    }
    return ans;
}
ll inverse_(ll a){
    return pow_(a,mod-2,mod);
}
ll get_(ll m, ll n){
    ll num = fact[m+n-2],
    den = fact[m-1]*fact[n-1]%mod;
    return num*inverse_(den)%mod;
}
int main() {
    fact[0]=1;
    for(ll i=1;i<=2000000;++i)
        fact[i] = fact[i-1]*i%mod;
    int T;
    scanf("%d",&T);
    while(T--){
        ll m, n;
        scanf("%lld%lld",&m,&n);
        printf("%lld\n",get_(m,n));
    }
    return 0;
}
