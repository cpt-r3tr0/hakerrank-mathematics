# include <iostream>
using namespace std;
typedef long long int ll;
const int maxn=400005;
const ll p=1e9+7;
ll fac[maxn],ifac[maxn];
ll M(ll a, ll b)
{
    if(b==0)return 1;
    if(b==1)return a;
    ll tmp;
    if(b&1)
        tmp=M(a,b-1)*a;
    else
        tmp=M(a,b/2),tmp*=tmp;
    if(tmp>=p)tmp%=p;
    return tmp;
}
ll C(int n,int r)
{
    if(n<r)return 0;
    ll tmp=fac[n]*ifac[n-r];
    if(tmp>=p)tmp%=p;
    tmp*=ifac[r];
    if(tmp>=p)tmp%=p;
    return tmp;
}
int main()
{
    cin.sync_with_stdio(false);
    cin.tie(0);
    fac[0]=ifac[0]=1;
    for(int i=1;i<maxn;i++)
    {
        fac[i]=(fac[i-1]*(1ll*i));
        if(fac[i]>=p)
            fac[i]%=p;
    }
    ifac[maxn-1]=M(fac[maxn-1],p-2);
    for(int i=maxn-2;i>=1;i--)
    {
        ifac[i]=ifac[i+1]*(1ll+i);
        if(ifac[i]>=p)
            ifac[i]%=p;
    }
    int t;
    cin>>t;
    while(t--)
    {
        ll n,lo,hi;
        cin>>n>>lo>>hi;
        ll coef=hi-lo;
        if(coef==0)
        {
            cout<<"1\n";
            continue;
        }
        ll res=0;
        ll clo=(n+2*coef)/(1+coef);
        for(int c=clo;c<=n;c++)
        {
            for(int k=0,alpha=0;k<=n-c;k+=c,alpha++)
            {
                ll tmp;
                    tmp=C(coef,alpha)*C(coef+n-c-k-1,n-c-k);
                    if(tmp>=p)tmp%=p;
                if(alpha&1)
                    res=(res-tmp+p)%p;
                else
                    res=(res+tmp+p)%p;
            }
        }
        res*=(coef+1);
        if(res>=p)res%=p;
        cout<<res<<"\n";
    }
    return 0;
}
