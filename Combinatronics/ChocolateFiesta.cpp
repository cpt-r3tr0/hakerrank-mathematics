#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define M 1000000007

using namespace std;

int n;
int a[100005];
long long dp[100005][2];

long long f(int idx, int flag)
{
    if ( idx == n ) {
         if ( !flag ) return 1;
         return 0;
    }
    long long &ans = dp[idx][flag];
    if ( ans != -1 ) return ans;
    ans = 0;
    ans += f(idx+1,flag)%M;
    ans %= M;
    ans += f(idx+1, (flag+a[idx])%2)%M;
    ans %= M;
    return ans;
}

int main()
{
    cin >> n;
    for ( int i = 0; i < n; i++ ) cin >> a[i];
    memset(dp, -1, sizeof(dp));
    long long ans = f(0,0);
    ans = (ans-1)%M;
    cout << ans << endl;
    return 0;
}
