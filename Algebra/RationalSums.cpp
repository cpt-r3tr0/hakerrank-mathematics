#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll m=1e9+7;
ll n,s,l,a[5005],b[5005],c[5005];
ll exp(ll l,ll r){
    ll s=1;
    while(r){
        if(r&1)
            s=s*l%m;
        l=l*l%m,r=r>>1;
    }
    return s;
}
ll cont(ll in){
    ll p=b[n-2],x=-a[in];
    for(int i=1;i<n-1;i++)
        p=(p*x%m+b[n-i-2])%m;
    ll q=1;
    for(int i=0;i<n;i++)
        q=q*(in==i?1:x+a[i])%m;
    return p*exp(q,m-2)%m;
}
int main() {
    cin>>n;
    for(int i=1;i<5005;i++)
        c[i]=(c[i-1]+exp(i,m-2))%m;
    for(int i=0;i<n;i++)
        cin>>a[i],l=max(l,a[i]);
    for(int i=0;i<n-1;i++)
        cin>>b[i];
    for(int i=0;i<n;i++)
        s=(cont(i)*(c[l]-c[a[i]])%m+s+m)%m;
    cout<<s<<endl;
    return 0;
}
