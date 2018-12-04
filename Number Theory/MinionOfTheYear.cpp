#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


#define REP(I, N) for (int I = 0; I < (N); ++I)
#define DRII(X, Y) int X, Y; scanf("%d%d", &X, &Y)

#define CASET int ___T, case_n = 1; scanf("%d ", &___T); while (___T-- > 0)

typedef long long LL;
using namespace std;
int MOD;
const int SIZE = 1e6+10;
int root;
LL mypow(LL x,LL y){
    LL res=1;
    while(y){
        if(y&1)res=res*x%MOD;
        y>>=1;
        x=x*x%MOD;
    }
    return res;
}
int find_root(int P){
    if(P==2)return 1;
    vector<int>fac;
    for(int i=2;i*i<=P-1;i++){
        if((P-1)%i==0)fac.push_back(i),fac.push_back(P/i);
    }
    int now=2;
    while(1){
        bool err=0;
        REP(i,fac.size()){
            if(mypow(now,fac[i])==1){
                err=1;
                break;
            }
        }
        if(!err)break;
        now++;
    }
    return now;
}
vector<pair<int,int> >pp;
int half,hv;
void pre(int P){
    root=find_root(P);
    int now=1;
    pp.clear();
    pp.push_back(make_pair(1,0));
    for(int i=1;i<P-1&&i<=1000000;i++){
        now=(LL)now*root%P;
        pp.push_back(make_pair(now,i));
        half=i;
        hv=now;
    }
    hv=mypow(hv,MOD-2);
    sort(pp.begin(), pp.end());
}
int get_id(int x){
    int ans=0;
    int it;
    while(1){
        it=lower_bound(pp.begin(), pp.end(),make_pair(x,0))-pp.begin();
        if(it!=pp.size()&&pp[it].first==x)break;
        ans+=half;
        x=(LL)x*hv%MOD;
    }
    return pp[it].second+ans;
}
// a*x+b*y=z
struct gcd_t {long long x,y,z;};
gcd_t gcd(long long a,long long b) {
    if(b==0)return (gcd_t){1,0,a};
    gcd_t t=gcd(b,a%b);
    return (gcd_t){t.y,t.x-t.y*(a/b),t.z};
}
int main(){
    CASET{
        DRII(P,N);
        MOD=P;
        pre(P);
        while(N--){
            DRII(A,B);
            DRII(C,D);
            if(A<B){swap(A,B);swap(C,D);}
            if(C%P==0&&D%P==0){
                printf("%d\n",A+B);
            }
            else if(C%P==0||D%P==0)puts("wala");
            else{
                C%=P;
                D%=P;
                if(P==2){
                    printf("%d\n",A+B);
                    continue;
                }
                C=get_id(C);
                D=get_id(D);
                if(C==0&&D==0){
                    printf("%d\n",A+B);
                    continue;
                }
                else if(C==0){
                    int gg=__gcd(D,P-1);
                    printf("%lld\n",A+(LL)B*(P-1)/gg);
                    continue;
                }
                else if(D==0){
                    int gg=__gcd(C,P-1);
                    printf("%lld\n",B+(LL)A*(P-1)/gg);
                    continue;
                }
                int M=P-1;
                {
                    int ha=__gcd(C,__gcd(D,M));
                    C/=ha;
                    D/=ha;
                    M/=ha;
                }
                int gg1=__gcd(D,M);
                int M2=M/gg1;
                LL now1=gg1/__gcd(gg1,C);
                gcd_t ker=gcd(D,M);
                while(ker.x<0)ker.x+=M2;
                LL now2=C*now1/ker.z%M2*ker.x%M2;
                D=now1;
                C=now2;
                if(now2==0)now2=M2;
                LL mi=A*now1+B*now2;
                while((LL)A*(now1+D)<mi){
                    now1+=D;
                    now2+=C;
                    if(now2>M2)now2-=M2;
                    mi=min(mi,A*now1+B*now2);
                }
                cout<<mi<<endl;
            }
        }
    }
    return 0;
}
