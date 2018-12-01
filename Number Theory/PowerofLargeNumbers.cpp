#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long int
#define ll long long int
#define uint unsigned int

#define read(n) scanf("%d",&n)
#define readll(n) scanf("%lld",&n)
#define read2(n,m) scanf("%d%d",&n,&m)
#define read3(n,m,l) scanf("%d%d%d",&n,&m,&l)

#define init(mem,v) memset(mem,v,sizeof(mem))
#define DB(x)              cout<<__LINE__<<" :: "<<#x<< ": "<<x<<endl;
#define DB2(x, y)          cout<<__LINE__<<" :: "<<#x<< ": "<<x<<" | "<<#y<< ": "<<y<<endl;
#define DB3(x, y, z)       cout<<__LINE__<<" :: "<<#x<< ": "<<x<<" | "<<#y<< ": "<<y<<" | "<<#z<<": "<<z<<endl;
#define DB4(a, b, c, d)    cout<<__LINE__<<" :: "<<#a<< ": "<<a<<" | "<<#b<< ": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl;
#define mod 1000000007

ll ppow(ll b,ll p){
    if(p==0) return 1;
    if(b==1) return 1;
    if(p%2==0){
        ll res=ppow(b,p/2);
        return (res*res)%mod;
    }
    return (b*ppow(b,p-1))%mod;
}

char A[100001],B[100001];
void solve(){
    scanf("%s %s",A,B);
    ll a=0;
    for(int i=0;A[i]!='\0';i++){
        a=(10*a+A[i]-'0')%mod;
    }
    ll res=1;
    for(int i=0;B[i]!='\0';i++){
        res=(ppow(res,10)*ppow(a,B[i]-'0'))%mod;
    }
    printf("%lld\n",res);
}

int main(){
    int t;
    read(t);
    while(t--) solve();
}
