#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define db long double
#define ii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define sz(a) (int)(a).size()
#define all(a) (a).begin(),(a).end()
#define pb push_back
#define mp make_pair
#define FN(i, n) for (int i = 0; i < (int)(n); ++i)
#define FEN(i,n) for (int i = 1;i <= (int)(n); ++i)
#define rep(i,a,b) for(i=a;i<b;i++)
#define repv(i,a,b) for(i=b-1;i>=a;i--)
#define SET(A, val) memset(A, val, sizeof(A))
typedef tree<int ,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set ;
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the kth largest element.(0-based)
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ','); cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
const int mod=1e9+7;
ll mult(ll x,ll y)
{
  x%=mod; y%=mod;
  ll tmp=(ll)x*y;
  if(tmp>=mod) tmp%=mod;
  return tmp;
}
ll add(ll x,ll y)
{
  x%=mod; y%=mod;
  x+=y;
  if(x>=mod) x-=mod;
  if(x<0) x+=mod;
  return x;
}
ll pow1(ll x,ll y)
{
  ll ans=1;
  while(y)
    {
      if(y&1) ans=mult(ans,x);
      x=mult(x,x);
      y>>=1;
    }
  return ans;
}
ll nc2(ll x)
{
  x%=mod;
  ll tmp=(ll)x*(x-1);
  tmp=mult(tmp,pow1(2,mod-2));
  return tmp;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  ll t,i,j;
  ll n;
  cin>>t;
  while(t--)
    {
      cin>>n;
      ll ans=0;
      ll sq=sqrt(n);
      rep(i,1,sq+1)
    {
      ll rem=n%i;
      ans=add(ans,mult(rem,nc2(n/i+1)));
      ans=add(ans,mult(i-rem,nc2(n/i)));
    }
      rep(i,1,sq+1)
    {
      if(n/i==sq) continue;
      ll l=n/(i+1)+1,r=n/i;
      l=min(l,r);
      ans=add(ans,mult(mult(r-l+1,n),i)); //n*x*(r-l+1)
      ans=add(ans,-mult(add(nc2(r+1),-nc2(l)),nc2(i+1)));//sum i*nc2(x+1)
    }
      cout<<add(ans,n)<<endl;
    }
  return 0 ;
}
