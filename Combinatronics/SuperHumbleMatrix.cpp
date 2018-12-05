#include<bits/stdc++.h>

#define ll long long int
#define MAX 2000005
const ll MOD=1e9+7;

using namespace std;
std::vector<int>adj[MAX];

int main()
{
    ll n,m;
    cin>>n>>m;
    ll fac[MAX]={0};
    fac[0]=1;
    for(ll i=1;i<MAX;i++)
        fac[i]=fac[i-1]*i%MOD;
    ll ans=1;
    for(ll i=1;i<=n;i++)
        ans=ans*fac[min(i,m)]%MOD;
    for(ll j=2;j<=m;j++)
        ans=ans*fac[min(m-j+1,n)]%MOD;
    cout<<ans<<endl;
    return 0;
}
