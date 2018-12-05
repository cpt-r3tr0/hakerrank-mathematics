#include <bits/stdc++.h>

using namespace std;

typedef long long     LL;
typedef pair<int,int> pii;

double PI  = acos(-1);
double EPS = 1e-7;
int INF    = 1000000000;
LL INFLL   = 1000000000000000000LL;

#define MAX(a, b)     (a) = max((a), (b))

int mx[8] = {-1,1,0,0,-1,-1,1,1};
int my[8] = {0,0,-1,1,-1,1,-1,1};

// ----- //

LL mod;

LL b[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int eh[4][4] = {{2,3,0,0},{31,73,0,0},{2,7,0,0},{2,13,0,0}};
inline LL multiply(LL a,LL b){
   a %= mod;
   b %= mod;
   long double res = a;
   res *= b;
   LL c = (LL)(res / mod);
   a *= b;
   a -= c * mod;
   a %= mod;
   if (a < 0) a += mod;
   return a;
}

inline LL power(LL a,LL b)
{
   LL ans=1;
   while(b)
   {
           if(b&1)
           {
                     ans=multiply(ans,a);
           }
           a=multiply(a,a);
           b>>=1;
   }
   return ans;
}

inline bool Miller(LL p)
{
    if(p<2)  return false;
    if(p!=2 && !(p&1)) return false;
    for(int i=0;i<25;i++)
    {
            if(p==b[i])return true;
            else if(p%b[i]==0)return false;
    }
    int count = 0;
    LL s=p-1;
    while(!(s&1))
    {
        s/=2;
        count++;
    }
    int ty;
    if (p < 1373653) ty = 0;
    else if (p < 9080191) ty = 1;
    else if (p < 4759123141LL) ty = 2;
    else ty = 3;
    for(int i=0;i<2;i++)
    {
        LL a=eh[ty][i];
        mod=p;
        LL x=power(a,s);
        if(x == 1 || x == p-1) continue;
        int flag = 0;
        for(int i = 1; i < count; i++)
        {
           x = multiply(x,x);
           if(x == 1) return false;
           if(x == p-1)
           {
              flag = 1;
              break;
           }
        }
        if(flag) continue;
        return false;
    }
    return true;
}

LL n;

inline __int128 ipow(__int128 base, int exp)
{
    __int128 result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

bool prime[1000005];
int nearprime[1000005];

void sieve(int n) {
  fill(prime, prime+n+1, 1);
  prime[1] = 0;
  for(int i = 2; i * i <= n; i++) {
    if (!prime[i]) continue;
    for(int j = 2 * i; j <= n; j += i) prime[j] = 0;
  }
}

vector<pair<LL, LL> > num[40];
LL lim = 1000000000000LL;

bool used[1000000];

LL solve(LL n, int k) {
  if (n == 0) return -1;
  if (k == 1) return 1;

  if (k == 2) {
    if (rand()%2 == 0 && n <= 1000000) {
      return nearprime[n];
    }

    for(LL i = n; i >= 0; i--) {
      if (Miller(i) && (i > 1000000 || !used[i])) return i;
    }
    return -1;
  }

  LL ans = -1;

    int i = upper_bound(num[k-1].begin(), num[k-1].end(), make_pair(n, (LL)INF)) - num[k-1].begin();
    while (i > 0) {
      if (num[k-1][i-1].second > 1000000 || !used[num[k-1][i-1].second]) {
        ans = num[k-1][i-1].first;
        break;
      }
      i--;
    }
  if (ans == n) return ans;

  for (int a = k-1; a >= 3; a--) {
    if (k%a) continue;
    for(pair<LL, LL> lol: num[a-1]) {
      if (lol.first > n) break;
      if (lol.second <= 1000000 && used[lol.second]) continue;
      LL yup = n/lol.first;
      if (yup*lol.first < ans) continue;

      if (lol.second <= 1000000)
      used[lol.second] = 1;
      MAX(ans, lol.first * solve(n/lol.first, k/a));
      if (lol.second <= 1000000)
      used[lol.second] = 0;

      if (ans == n) return ans;
    }
  }

  if (k&(k-1));
  else {

    int a = 2;
    for(pair<LL, LL> lol: num[a-1]) {
      if (lol.first*lol.first > n) break;
      if (lol.second < 1000000 && used[lol.second]) continue;
      LL yup = n/lol.first;
      if (yup*lol.first < ans) continue;

      if (lol.second <= 1000000)
      used[lol.second] = 1;
      MAX(ans, lol.first * solve(n/lol.first, k/a));

      if (lol.second <= 1000000)
      used[lol.second] = 0;

      if (ans == n) return ans;
    }
  }

  return ans;


}

int main() {
  sieve(1000000);
  int yo = -1;
  for (int a = 1; a <=1000000; a++){
    if (prime[a]) yo = a;

    nearprime[a] = yo;
  }

  for (int b = 2; b<=1000000; b++){
    if (!prime[b]) continue;
    num[1].push_back(make_pair(b, (LL)b));
  }

  for (int a = 2; a <=39; a++){
    for (int b = 2; b <=1000000; b++){
      if (!prime[b]) continue;
      __int128 res = ipow(b, a);
      if (res > lim) break;
      num[a].push_back(make_pair((LL)res, (LL)b));
    }
  }

  int t;
  scanf("%d",&t);
  while(t--) {
    int k;
    scanf("%lld %d",&n,&k);
    cout << solve(n, k) << endl;
  }
}
