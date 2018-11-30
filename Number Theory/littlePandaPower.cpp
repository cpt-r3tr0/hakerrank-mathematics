
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<stdio.h>
#include<math.h>
using namespace std;
#define ll long long int
#define FOR(i,a,b) for(i= (int )a ; i < (int )b ; ++i)
#define rep(i,n) FOR(i,0,n)
#define INF INT_MAX
#define pb push_back
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define pi(n) printf("%d ",n)
#define pd(n) printf("%lf ",n)
#define pdl(n) printf("%lf\n",n)
#define pin(n) printf("%d\n",n)
#define pl(n) printf("%lld",n)
#define pln(n) printf("%lld\n",n)
#define si(n) scanf("%d",&n)
#define sl(n) scanf("%lld",&n)
#define scan(v,n) vector<int> v;rep(i,n){ int j;si(j);v.pb(j);}
#define mod (int)(1e9 + 7)

int isprime[1000006];
vector<int> primeit;
void seive()
{
    int i,j;
    int MAX=1000006;
    isprime[0] = isprime[1] = 1;
    for (i = 4; i < MAX; i += 2)
        isprime[i] = 1;
    for (i = 3; i * i < MAX; i += 2)
    {
        if (!isprime[i])
        {
            for (j = i * i; j < MAX; j += 2 * i)
                {
                    isprime[j] = 1;
                }
        }
    }
    for(i=2;i<=MAX;i++)
        if(!isprime[i])
            primeit.pb(i);
}
ll gcd(ll a, ll b)
{
    ll c;
    while(a!=0)
    {
        c=a;
        a=b%a;
        b=c;
    }
    return b;
}
ll powerit(ll a, ll b, ll c)
{
    ll x=1;
    while(b!=0)
    {
        if(b&01==1)
        {
            x*=a;
            if(x>=c)
                x%=c;
        }
        a=a*a;
        if(a>=c)
            a%=c;
        b>>=1;
    }
    return x;
}

int main()
{
    int t,cnt;
    ll a,b,c,sqrtit,calc1,calc2,calcit,b1,ansit,c4,c1;
    //Finding all prime factors which will be required to compute phi(n)
    seive();
    si(t);
    while(t--)
    {
        b1=1;
        sl(a);
        sl(b);
        sl(c);
        c1=c;
        if(b<0)
        {
            cnt=0;
            calc1=c;
            calc2=1;
            //Calculating phi(n)
            //Using the formula phi(n)=n*(1-1/p1)*(1-1/p2)* ..... where pi refers to all prime divisors
            sqrtit=sqrt(calc1);
            sqrtit++;
            //Finding all prime factors which is less than sqrt(n) and using the formula above
            while(primeit[cnt]<=sqrtit)
            {
                calcit=primeit[cnt];
                if(c%calcit==0)
                {
                    calc1*=(calcit-1);
                    calc2*=calcit;
                    c4=gcd(calc1,calc2);
                    calc1/=c4;
                    calc2/=c4;
                    while(c%calcit==0)
                        c/=calcit;
                }
                cnt++;
            }
            if(c!=1 && isprime[c]==0)
            {
                calc1*=(c-1);
                calc2*=c;
            }
            calc1/=calc2;
            //phi(n) is calculated and stored in calc1
            b1=calc1-1;
            b=-b;
        }
        //To calculate ansit=A^(-1)%x using phi(x)
        ansit=powerit(a,b1,c1);
        //To calculate ansit=(ansit^b)%x
        ansit=powerit(ansit,b,c1);
        pln(ansit);
    }
    return 0;
}
