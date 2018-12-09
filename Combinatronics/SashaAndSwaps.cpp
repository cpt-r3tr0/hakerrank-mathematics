#include <bits/stdc++.h>

using namespace std;
#define MP make_pair
#define PB push_back
#define LL long long
#define int LL
#define FI first
#define SE second
#define R(i,n) for(int i=0;i<n;i++)
#define F(i,a,b) for(int i=a;i<b;i++)
#define FD(i,n) for(int i=n-1;i>=0;i--)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define PII pair<int,int>
#define VI vector<int>
template<class C> void mini(C&a4, C b4){a4=min(a4,b4);}
template<class C> void maxi(C&a4, C b4){a4=max(a4,b4);}

template<class TH> void _dbg(const char *sdbg, TH h){cerr<<sdbg<<"="<<h<<"\n";}
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a){
  while(*sdbg!=',')cerr<<*sdbg++;cerr<<"="<<h<<","; _dbg(sdbg+1,a...);
}

#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#define debugv(C) {for(auto&c:C)cerr<<c<<",";cerr<<endl;}
#else
#define debug(...) (__VA_ARGS__)
#define debugv(C) {}
#define cerr if(0) cout
#endif
#define MAX 100001
vector<vector<int>> cykle[MAX];
void nie(){
  cout << "no solution\n";
  exit(0);
}
int n,k,t;
int in[MAX];
int wyn[MAX];
bool cz[MAX];
#undef int
int main(){
#define int LL
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(11);
  cin >> n >> k >> t;
  R(i,n){
    cin >> in[i];
    in[i]--;
  }
  R(i,n)if(cz[i] == 0){
    vector<int> cykl;
    int ak = i;
    while(cz[ak] == 0){
      cz[ak] = 1;
      cykl.PB(ak);
      ak = in[ak];
    }
    cykle[SZ(cykl)].PB(cykl);
  }
  vector<PII> res,res2;
  bool czzl = 0;
  F(i,1,n+1)if(SZ(cykle[i])){
    int pom = __gcd(i,t);
    while(1){
      int pom2 = __gcd(pom*pom,t);
      if(pom2 == pom)break;
      pom = pom2;
    }
    debug(i,SZ(cykle[i]),pom);
    if(SZ(cykle[i]) % pom != 0)nie();
    R(j,SZ(cykle[i])/pom){
      R(k,pom){
        int ak = k;
        for(auto x:cykle[i][j*pom+k]){
          wyn[ak] = x;
          ak = (ak+t)%(i*pom);
        }
      }
      R(j,i*pom-1)res.PB({wyn[j],wyn[j+1]});
      R(j,i*pom-1)res2.PB({wyn[j],wyn[j+1]});
    }
    if(czzl == 0 && t%2 == 0 && pom%2 != 0 && SZ(cykle[i])%2 == 0){
      czzl = 1;
      res2.resize(SZ(res2)-2*i*pom+2);
      R(k,pom*2){
        int ak = k;
        for(auto x:cykle[i][SZ(cykle[i])-k-1]){
          wyn[ak] = x;
          ak = (ak+t)%(2*i*pom);
        }
      }
      R(j,2*i*pom-1)res2.PB({wyn[j],wyn[j+1]});
    }
  }
  debug(k,SZ(res),czzl,SZ(res2));
  if(k < SZ(res) || (czzl == 0 && (k+SZ(res))%2 != 0))nie();
  if((k+SZ(res))%2 != 0){
    debug("swap!!!!!!!!!!!!!!!!!!!!1");
    swap(res,res2);
  }
  while(k!=SZ(res)){
    res.PB({0,1});
    res.PB({0,1});
  }
  for(auto x:res){
    cout << x.FI+1  << " " << x.SE+1 << "\n";
  }
}
