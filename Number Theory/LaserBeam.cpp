#include <bits/stdc++.h>

typedef long long LL;

using namespace std;

const int MOD = 1e9+7;
LL dp3[600000],mul[600000],record[600000];

int main(){
  for(int i = 1; i < 600000; ++i){
    dp3[i]+=(LL)(i+i+1)*(i+i+1)*(i+i+1)-(LL)(i+i-1)*(i+i-1)*(i+i-1);
    for(int j=i+i;j<600000;j+=i){
      dp3[j]-=dp3[i];
    }
    dp3[i]+=dp3[i-1];
    dp3[i]%=MOD;
  }
  int ___T,
  case_n = 1;
  scanf("%d ", &___T);
  while (___T-- > 0){
      memset(record, 0, sizeof(record));
      memset(mul, 0, sizeof(mul));
      LL N,an=0;
      int M,D;
      scanf("%lld%d%d",&N,&M,&D);
      LL now=1;
      while(now<=N){
          LL v=N/now;
          LL nxt=N/v;
          if(v>=M){
              if(v%D==0){
                  if(nxt<600000)
                      an+=dp3[nxt];
                  else
                      mul[v]++;
                  if(now-1<600000)
                      an-=dp3[now-1];
                  else
                      mul[v+1]--;
              }
          }
          now=nxt+1;
      }
      int ker=1;
      while(N/ker>=600000)ker++;
      int bb=ker;
      for(ker--;ker>0;ker--){
          LL n=N/ker;
          LL me=(n+n+1)%MOD;
          record[ker]=(me*me%MOD*me%MOD-1);
          for(now=2;ker*now<bb;now++)
              record[ker]-=record[ker*now];
          while(now<=n){
              LL v=n/now;
              LL nxt=n/v;
              if(v<600000){
                  record[ker]-=dp3[v]*(nxt-now+1);
                  record[ker]%=MOD;
              }
              now=nxt+1;
          }
          record[ker]%=MOD;
          if(record[ker]<0)record[ker]+=MOD;
          if(mul[ker])an+=mul[ker]*record[ker];
        }
        an%=MOD;
        if(an<0)an+=MOD;
        cout<<an<<endl;
      }
      return 0;
}
