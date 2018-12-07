#include<stdio.h>
#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>

#define MOD 1000000007
#define INF 2000000000

using namespace std;

long long powmod(long long b,long long e)
{
     long long ret=1;

     while(e)
     {
             if(e&1)
             {
                    ret*=b;
                    ret%=MOD;
             }
             b*=b;
             b%=MOD;
             e>>=1;
     }

     return ret;
}

long long fact[3000];

long long ncr(int i,int j)
{
     long long ret=fact[i];

     ret*=powmod(fact[j],MOD-2);
     ret%=MOD;
     ret*=powmod(fact[i-j],MOD-2);
     ret%=MOD;
     return ret;
}

int main()
{
    int t,n,m;

    long long i;

    fact[0]=1;


    for(i=1;i<=2005;i++)
    {
                    fact[i]=(i*fact[i-1])%MOD;
    }

    scanf("%d",&t);

    while(t--)
    {
              scanf("%d %d",&n,&m);
              m--;
              printf("%lld\n",ncr(n+m,m));
    }

    return 0;
}
